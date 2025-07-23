//
// Created by loghin on 7/16/25.
//

#ifndef CDS_DS_JSON_PRINTER_OUTPUT_STREAM_HPP
#define CDS_DS_JSON_PRINTER_OUTPUT_STREAM_HPP
#pragma once

#include "JsonPrinterOutput.hpp"
#include "JsonPrinterIndenter.hpp"
#include "InvalidUTF8EncodingException.hpp"

#include <cds/meta/ObjectTraits>

namespace cds {
namespace json {
namespace impl {
using meta::EnableIf;
using meta::IsFloating;
using meta::IsIntegral;
using meta::Void;
using meta::lvalue;

template <typename StreamType>
struct JsonPrinterOutput<StreamType, Void<decltype(lvalue<StreamType>() << "")>> {
  CDS_ATTR(constexpr(11)) JsonPrinterOutput(JsonPrinterContext& ctx, StreamType& out) noexcept :
      ctx{ctx},
      out{out} {}

  CDS_ATTR(constexpr(20)) auto forceWrite(char value) noexcept -> void {
    out << value;
    onLine += 1;
  }

  CDS_ATTR(constexpr(20)) auto forceWrite(StringView value) noexcept -> void {
    out << value;
    onLine += value.length();
  }

  template <Size n> CDS_ATTR(constexpr(20)) auto forceWrite(char const(&cStr)[n]) noexcept -> void {
    forceWrite(StringView{cStr, n - 1});
  }

  CDS_ATTR(constexpr(20)) auto forceWrite(bool value) noexcept -> void {
    forceWrite(value ? StringView{"true"} : StringView{"false"});
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(constexpr(20)) auto forceWrite(N value) noexcept -> void {
    auto const before = out.tellp();
    out << value;
    onLine += out.tellp() - before;
  }

  template <typename N, EnableIf<IsFloating<N>> = 0>
  CDS_ATTR(constexpr(20)) auto forceWrite(N value) noexcept -> void {
    auto const before = out.tellp();
    out << value;
    onLine += out.tellp() - before;
  }

  CDS_ATTR(constexpr(20)) auto forceWriteEscaped(StringView value) noexcept -> void {
    if (ctx.options.printNonAsciiAsUTFCodePoints) {
      return forceWriteEscapedUTF(value);
    }

    forceWrite('"');
    for (auto c : value) {
      auto escaped = true;
      if (c == '\t') {
        c = 't';
      } else if (c == '\n') {
        c = 'n';
      } else if (c == '\r') {
        c = 'r';
      } else if (c == '\f') {
        c = 'f';
      } else if (c == '"' || c == '\\') {
        // nothing
      } else {
        escaped = false;
      }

      if (escaped) {
        forceWrite('\\');
      }
      forceWrite(c);
    }
    forceWrite('"');
  }

  CDS_ATTR(constexpr(20)) auto forceWriteEscapedUTF(StringView value) CDS_ATTR(noexcept(false)) -> void {
    forceWrite('"');

    for (Size idx = 0u; idx < value.length(); ++idx) {
      if (0 == (static_cast<U8>(value[idx]) & 0x80u)) {
        auto c = value[idx];
        auto escaped = true;
        if (c == '\t') {
          c = 't';
        } else if (c == '\n') {
          c = 'n';
        } else if (c == '\r') {
          c = 'r';
        } else if (c == '\f') {
          c = 'f';
        } else if (c == '"' || c == '\\') {
          // nothing
        } else {
          escaped = false;
        }

        if (escaped) { forceWrite('\\'); }
        forceWrite(c);
        continue;
      }

      out << "\\u";
      auto toHexChar = [](U8 value) -> char {
        return value < 10
            ? static_cast<char>('0' + value)
            : static_cast<char>('a' + (value - 10));
      };

      if (0xC0u == (value[idx] & 0xE0u)) {
        if (idx + 1 >= value.length()
            || (value[idx + 1] & 0xC0u) != 0x80u) {
          throw InvalidUTF8EncodingException();
        }
        out << '0'
            << toHexChar((value[idx] & 0x1Cu) >> 2u)
            << toHexChar(((value[idx] & 0x03u) << 2u) | ((value[idx + 1] & 0x30u) >> 4u))
            << toHexChar(value[idx + 1] & 0x0Fu);
        ++idx;
      } else if (0xE0u == (value[idx] & 0xF0u)) {
        if (idx + 2 >= value.length()
            || (value[idx + 1] & 0xC0u) != 0x80u
            || (value[idx + 2] & 0xC0u) != 0x80u) {
          throw InvalidUTF8EncodingException();
        }
        out << toHexChar(value[idx] & 0x0Fu);
        out << toHexChar((value[idx + 1] & 0x3Cu) >> 2u);
        out << toHexChar(((value[idx + 1] & 0x03u) << 2u) | ((value[idx + 2] & 0x30u) >> 4u));
        out << toHexChar(value[idx + 2] & 0x0Fu);
        idx += 2;
      } else {
        // writing 0x10000 - 0x10FFFF not directly supported as parsing these codepoints is, in itself, unsupported
        // in the JSON standard
        // Furthermore, anything else is an encoding error
        throw InvalidUTF8EncodingException();
      }
      onLine += 6;
    }
    forceWrite('"');
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto fits(Size const count) const noexcept -> bool {
    return onLine + count <= ctx.options.columnLimit;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto fits(char) const noexcept -> bool {
    return onLine + 1 <= ctx.options.columnLimit;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto fits(StringView value) const noexcept -> bool {
    return fits(value.length());
  }

  auto write(char value) noexcept -> bool {
    if (!fits(value)) {
      return false;
    }

    forceWrite(value);
    return true;
  }

  auto write(StringView value) noexcept -> bool {
    if (!fits(value)) {
      return false;
    }

    forceWrite(value);
    return true;
  }

  auto finishLine(StringView eol) noexcept -> void {
    out << eol;
    onLine = 0u;
  }

  auto indenter() noexcept -> JsonPrinterIndenter<JsonPrinterOutput> {
    return JsonPrinterIndenter<JsonPrinterOutput>{*this};
  }

  JsonPrinterContext& ctx;
  StreamType& out;
  U32 onLine{0u};
};
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_PRINTER_OUTPUT_STREAM_HPP
