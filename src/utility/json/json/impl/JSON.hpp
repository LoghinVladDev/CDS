//
// Created by loghin on 08/11/22.
//

#ifndef __CDS_JSON_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_JSON_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace json {      // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_NoDiscard __CDS_cpplang_ConstexprMultipleReturn auto __jet_toString(  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables) 
   __JsonElementType type
) noexcept -> StringLiteral {
  switch (type) {
    case __JsonElementType::__jet_Object:   { return "JsonObject"; }
    case __JsonElementType::__jet_Array:    { return "JsonArray"; }
    case __JsonElementType::__jet_String:   { return "String"; }
    case __JsonElementType::__jet_Bool:     { return "bool"; }
    case __JsonElementType::__jet_Long:     { return "long"; }
    case __JsonElementType::__jet_Double:   { return "double"; }
    default:
    case __JsonElementType::__jet_Invalid:  { return "invalid"; }
  }
}

auto __parseJsonObject( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    StringView const& string,
    Size              offset,
    Size              length,
    json::JsonObject& into
) noexcept(false) -> Size;

auto __parseJsonArray(  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    StringView const& string,
    Size              offset,
    Size              length,
    json::JsonArray&  into
) noexcept(false) -> Size;

auto __dumpIndented(  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    JsonObject const& object,
    Size              indent,
    Size              depth
) noexcept -> String;

auto __dumpIndented(  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    JsonArray const&  object,
    Size              indent,
    Size              depth
) noexcept -> String;

auto __dumpIndented(  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    JsonElement const&  object,
    Size                indent,
    Size                depth
) noexcept -> String;

auto __dumpIndented(  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    MapEntry<String, JsonElement> const&  object,
    Size                                  indent,
    Size                                  depth
) noexcept -> String;

inline auto __parseJsonObject( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-function-cognitive-complexity)
    StringView const& string,
    Size              offset, // NOLINT(*-easily-swappable-parameters)
    Size              length, // NOLINT(*-easily-swappable-parameters)
    json::JsonObject& into
) noexcept(false) -> Size {
  enum class State {
    ExpectingLabel,
    ReadingLabel,
    ExpectingLVSeparator,
    ReadingValue,
    ReadingStringValue,
    ReadingNumericValue,
    ReadingBase2,
    ReadingBase8,
    ReadingBase10,
    ReadingBase16,
    ReadingBoolValue,
    ExpectingPSeparator
  };

  State   state         = State::ExpectingLabel;
  bool    readBackslash = false;
  bool    readFloat     = false;
  String  label;
  String  stringData;

  // assume string [0] is right after '{'
  for (Size index = offset; index < length; ++index) { // NOLINT(*-init-variables)
    switch (state) {
      case State::ExpectingLabel: {
        // skip all following whitespace 
        while (String::whitespace.contains(string[index])) {
          ++index;
        }

        // expecting json input -> "label" : object, "label" : object .... 
        if (string[index] == '}') {
          return index;
        }

        if (string[index] != '"') {
          throw JsonFormatException('"', '{', string[index]);
        }

        state = State::ReadingLabel;
        break;
      }

      case State::ReadingLabel: {
        if (string[index] == '\\') {
          readBackslash = true;
          break;
        }

        if (!readBackslash && string[index] == '"') {
          state = State::ExpectingLVSeparator;
        } else if (readBackslash) {
          if (string[index] == 'n') {
            label += '\n';
          } else if (string[index] == 't') {
            label += '\t';
          } else if (string[index] == 'f') {
            label += '\f';
          } else if (string[index] == 'r') {
            label += '\r';
          } else if (string[index] == 'v') {
            label += '\v';
          } else if (string[index] == 'a') {
            label += '\a';
          } else if (string[index] == 'b') {
            label += '\b';
          }
        } else {
          label += string[index];
        }

        readBackslash = false;
        break;
      }

      case State::ExpectingLVSeparator: {
        // skip all following whitespace 
        while (String::whitespace.contains(string[index])) {
          ++index;
        }

        if (string[index] != ':') {
          throw JsonFormatException(':', label, string[index]);
        }

        state = State::ReadingValue;
        break;
      }

      case State::ReadingValue: {
        // skip all following whitespace
        while (String::whitespace.contains(string[index])) {
          ++index;
        }

        if (string[index] == '{') {
          JsonObject object; // NOLINT(cppcoreguidelines-init-variables) 
          index = __parseJsonObject(string, index + 1u, length, object);
          into.emplace(std::move(label), std::move(object));
          state = State::ExpectingPSeparator;
          break;
        }

        if (string[index] == '[') {
          JsonArray array; // NOLINT(cppcoreguidelines-init-variables) 
          index = __parseJsonArray(string, index + 1u, length, array);
          into.emplace(std::move(label), std::move(array));
          state = State::ExpectingPSeparator;
          break;
        }

        if (string[index] == '"') {
          state = State::ReadingStringValue;
          break;
        }

        state = State::ReadingNumericValue;
        --index;
        break;
      }

      case State::ReadingStringValue: {
        if (string[index] == '\\') {
          readBackslash = true;
          break;
        }

        if (!readBackslash && string[index] == '"') {
          state = State::ExpectingPSeparator;
          into.emplace(std::move(label), std::move(stringData));
        } else if (readBackslash) {
          if (string[index] == 'n') {
            stringData += '\n';
          } // NOLINT(bugprone-branch-clone) 
          else if (string[index] == 't') {
            stringData += '\t';
          } else if (string[index] == 'f') {
            stringData += '\f';
          } else if (string[index] == 'r') {
            stringData += '\r';
          } else if (string[index] == 'v') {
            stringData += '\v';
          } else if (string[index] == 'a') {
            stringData += '\a';
          } else if (string[index] == 'b') {
            stringData += '\b';
          }
        } else {
          stringData += string[index];
        }

        readBackslash = false;
        break;
      }

      case State::ReadingNumericValue: {
        if (StringView("tTfF").contains(string[index])) {
          --index;
          state = State::ReadingBoolValue;
        } else if (string[index] == '0' && index + 1 < length) {
          if (string[index + 1] == 'x' || string[index + 1] == 'X') {
            ++index;
            state = State::ReadingBase16;
          } else if (string[index + 1] == 'b' || string[index + 1] == 'B') {
            ++index;
            state = State::ReadingBase2;
          } else if (StringUtils<char>::isDigit(string[index + 1])) {
            state = State::ReadingBase8;
          } else {
            state = State::ReadingBase10;
          }
        } else {
          // only 0 case 
          --index;
          state = State::ReadingBase10;
        }

        break;
      }

      case State::ReadingBoolValue: {
        if (index + 4 >= length) { throw JsonFormatException("true/false", "t/f/T/F", "Unexpected end of String"); }
        if (
            (string[index] == 'T' || string[index] == 't')
            && string[index + 1] == 'r'
            && string[index + 2] == 'u'
            && string[index + 3] == 'e'
        ) {
          index += 3u;
          into.emplace(std::move(label), true);
          state = State::ExpectingPSeparator;
          break;
        }

        if (index + 5 >= length) {
          throw JsonFormatException("false", "t/f/T/F", "Unexpected end of String");
        } // NOLINT(*-magic-numbers) 

        if (
            (string[index] == 'F' || string[index] == 'f')
            && string[index + 1] == 'a'
            && string[index + 2] == 'l'
            && string[index + 3] == 's'
            && string[index + 4] == 'e'
        ) {
          index += 4u;
          into.emplace(std::move(label), false);
          state = State::ExpectingPSeparator;
          break;
        }

        throw JsonFormatException(
            "true/false", "t/f/T/F", string.substr(index, index + 5) + " does not represent any bool value"  // NOLINT(*-magic-numbers)
        );
      }

      case State::ReadingBase2: {
        while (string[index] == '0' || string[index] == '1') {
          stringData += string[index++];
        }
        into.emplace(std::move(label), std::strtoll(stringData.cStr(), nullptr, 2));
        stringData.clear();
        --index;
        state = State::ExpectingPSeparator;
        break;
      }

      case State::ReadingBase8: {
        while (string[index] >= '0' && string[index] <= '7') {
          stringData += string[index++];
        }
        into.emplace(std::move(label), std::strtoll(stringData.cStr(), nullptr, 8));
        stringData.clear();
        --index;
        state = State::ExpectingPSeparator;
        break;
      }

      case State::ReadingBase16: {
        while (
            string[index] >= '0' && string[index] <= '9'
            || string[index] >= 'a' && string[index] <= 'f'
            || string[index] >= 'A' && string[index] <= 'F'
        ) {
          stringData += string[index++];
        }

        into.emplace(std::move(label), std::strtoll(stringData.cStr(), nullptr, 16));
        stringData.clear();
        --index;
        state = State::ExpectingPSeparator;
        break;
      }

      case State::ReadingBase10: {
        while (string[index] >= '0' && string[index] <= '9' || string[index] == '.') {
          if (string[index] == '.') {
            readFloat = true;
          }
          stringData += string[index++];
        }

        if (readFloat) {
          into.emplace(std::move(label), std::strtod(stringData.cStr(), nullptr));
          readFloat = false;
        } else {
          into.emplace(std::move(label), std::strtoll(stringData.cStr(), nullptr, 10));
        }

        stringData.clear();
        --index;
        state = State::ExpectingPSeparator;
        break;
      }

      case State::ExpectingPSeparator: {
        // skip all following whitespace 
        while (String::whitespace.contains(string[index])) {
          ++index;
        }

        if (string[index] == '}') {
          return index;
        }

        if (string[index] == ',') {
          state = State::ExpectingLabel;
          break;
        }

        throw JsonFormatException(",/}", "label:value", String("Unexpected character : ") + string[index]);
      }
    }
  }

  switch (state) {
    case State::ExpectingLabel:       { throw JsonFormatException("label", "','", "Unexpected End of String"); }
    case State::ReadingLabel:         { throw JsonFormatException("\"", "label", "Unexpected End of String"); }
    case State::ExpectingLVSeparator: { throw JsonFormatException("':'", "label", "Unexpected End of String"); }
    case State::ReadingValue:         { throw JsonFormatException("value", "':'", "Unexpected End of String"); }
    case State::ReadingStringValue:   { throw JsonFormatException("string value", "\"", "Unexpected End of String"); }
    case State::ReadingNumericValue:  { throw JsonFormatException("digit", "no string/json/array value id", "Unexpected End of String"); }
    case State::ReadingBase2:         { throw JsonFormatException("0/1", "0b/0B", "Unexpected End of String"); }
    case State::ReadingBase8:         { throw JsonFormatException("0-7", "0", "Unexpected End of String"); }
    case State::ReadingBase10:        { throw JsonFormatException("0-9", "numeric value", "Unexpected End of String"); }
    case State::ReadingBase16:        { throw JsonFormatException("0-9/a-f/A-F", "0x/0X", "Unexpected End of String"); }
    case State::ReadingBoolValue:     { throw JsonFormatException("true/True/false/False", "t/f/T/F", "Unexpected End of String"); }
    case State::ExpectingPSeparator:  { throw JsonFormatException(",", "value", "Unexpected End of String"); }
  }

  // unlikely to be reached 
  return length;
}


inline auto __parseJsonArray( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-function-cognitive-complexity)
    StringView const& string,
    Size              offset, // NOLINT(bugprone-easily-swappable-parameters)
    Size              length, // NOLINT(bugprone-easily-swappable-parameters)
    json::JsonArray&  into
) noexcept(false) -> Size {
  enum class State {
    ReadingValue,
    ReadingStringValue,
    ReadingNumericValue,
    ReadingBase2,
    ReadingBase8,
    ReadingBase10,
    ReadingBase16,
    ReadingBoolValue,
    ExpectingPSeparator
  };

  State   state         = State::ReadingValue;
  bool    readBackslash = false;
  bool    readFloat     = false;
  String  label;      // NOLINT(cppcoreguidelines-init-variables)
  String  stringData; // NOLINT(cppcoreguidelines-init-variables)

  // assume string [offset] is right after '['
  for (Size index = offset; index < length; ++index) { // NOLINT(cppcoreguidelines-init-variables)
    switch (state) {
      case State::ReadingValue: {
        // skip all following whitespace 
        while (String::whitespace.contains(string[index])) {
          ++index;
        }

        if (string[index] == ']') {
          return index;
        }

        if (string[index] == '{') {
          JsonObject object; // NOLINT(cppcoreguidelines-init-variables) 
          index = __parseJsonObject(string, index + 1u, length, object);
          into.pushBack(std::move(object));
          state = State::ExpectingPSeparator;
          break;
        }

        if (string[index] == '[') {
          JsonArray array; // NOLINT(cppcoreguidelines-init-variables) 
          index = __parseJsonArray(string, index + 1u, length, array);
          into.pushBack(std::move(array));
          state = State::ExpectingPSeparator;
          break;
        }

        if (string[index] == '"') {
          state = State::ReadingStringValue;
          break;
        }

        state = State::ReadingNumericValue;
        --index;
        break;
      }

      case State::ReadingStringValue: {
        if (string[index] == '\\') {
          readBackslash = true;
          break;
        }

        if (!readBackslash && string[index] == '"') {
          state = State::ExpectingPSeparator;
          into.pushBack(std::move(stringData));
        } else if (readBackslash) {
          if (string[index] == 'n') {
            stringData += '\n';
          } else if (string[index] == 't') {
            stringData += '\t';
          } else if (string[index] == 'f') {
            stringData += '\f';
          } else if (string[index] == 'r') {
            stringData += '\r';
          } else if (string[index] == 'v') {
            stringData += '\v';
          } else if (string[index] == 'a') {
            stringData += '\a';
          } else if (string[index] == 'b') {
            stringData += '\b';
          }
        } else {
          stringData += string[index];
        }

        readBackslash = false;
        break;
      }

      case State::ReadingNumericValue: {
        if (StringView("tTfF").contains(string[index])) {
          --index;
          state = State::ReadingBoolValue;
        } else if (string[index] == '0' && index + 1 < length) {
          if (string[index + 1] == 'x' || string[index + 1] == 'X') {
            ++index;
            state = State::ReadingBase16;
          } else if (string[index + 1] == 'b' || string[index + 1] == 'B') {
            ++index;
            state = State::ReadingBase2;
          } else if (StringUtils<char>::isDigit(string[index + 1])) {
            state = State::ReadingBase8;
          } else {
            state = State::ReadingBase10;
          }
        } else {
          // only 0 case
          --index;
          state = State::ReadingBase10;
        }

        break;
      }

      case State::ReadingBoolValue: {
        if (index + 4 >= length) { throw JsonFormatException("true/false", "t/f/T/F", "Unexpected end of String"); }
        if (
            (string[index] == 'T' || string[index] == 't')
            && string[index + 1] == 'r'
            && string[index + 2] == 'u'
            && string[index + 3] == 'e'
        ) {
          index += 3u;
          into.pushBack(true);
          state = State::ExpectingPSeparator;
          break;
        }

        if (index + 5 >= length) {
          throw JsonFormatException("false", "t/f/T/F", "Unexpected end of String");
        } // NOLINT(*-magic-numbers) 

        if (
            (string[index] == 'F' || string[index] == 'f')
            && string[index + 1] == 'a'
            && string[index + 2] == 'l'
            && string[index + 3] == 's'
            && string[index + 4] == 'e'
        ) {
          index += 4u;
          into.pushBack(false);
          state = State::ExpectingPSeparator;
          break;
        }

        throw JsonFormatException(
            "true/false", "t/f/T/F", string.substr(index, index + 5) + " does not represent any bool value"  // NOLINT(*-magic-numbers)
        );
      }

      case State::ReadingBase2: {
        while (string[index] == '0' || string[index] == '1') {
          stringData += string[index++];
        }
        into.pushBack(std::strtoll(stringData.cStr(), nullptr, 2));
        stringData.clear();
        --index;
        state = State::ExpectingPSeparator;
        break;
      }

      case State::ReadingBase8: {
        while (string[index] >= '0' && string[index] <= '7') {
          stringData += string[index++];
        }
        into.pushBack(std::strtoll(stringData.cStr(), nullptr, 8));
        stringData.clear();
        --index;
        state = State::ExpectingPSeparator;
        break;
      }

      case State::ReadingBase16: {
        while (
            string[index] >= '0' && string[index] <= '9'
            || string[index] >= 'a' && string[index] <= 'f'
            || string[index] >= 'A' && string[index] <= 'F'
        ) {
          stringData += string[index++];
        }

        into.pushBack(std::strtoll(stringData.cStr(), nullptr, 16));
        stringData.clear();
        --index;
        state = State::ExpectingPSeparator;
        break;
      }

      case State::ReadingBase10: {
        while (string[index] >= '0' && string[index] <= '9' || string[index] == '.') {
          if (string[index] == '.') {
            readFloat = true;
          }
          stringData += string[index++];
        }

        if (readFloat) {
          into.pushBack(std::strtod(stringData.cStr(), nullptr));
          readFloat = false;
        } else {
          into.pushBack(std::strtoll(stringData.cStr(), nullptr, 10));
        }

        stringData.clear();
        --index;
        state = State::ExpectingPSeparator;
        break;
      }

      case State::ExpectingPSeparator: {
        // skip all following whitespace 
        while (String::whitespace.contains(string[index])) {
          ++index;
        }

        if (string[index] == ']') {
          return index;
        }

        if (string[index] == ',') {
          state = State::ReadingValue;
          break;
        }

        throw JsonFormatException("','/']'", "label:value", String("Unexpected character : ") + string[index]);
      }
    }
  }

  switch (state) {
    case State::ReadingValue:         { throw JsonFormatException("value", "'['/','", "Unexpected End of String"); }
    case State::ReadingStringValue:   { throw JsonFormatException("string value", "\"", "Unexpected End of String"); }
    case State::ReadingNumericValue:  { throw JsonFormatException("digit", "no string/json/array value id", "Unexpected End of String"); }
    case State::ReadingBase2:         { throw JsonFormatException("0/1", "0b/0B", "Unexpected End of String"); }
    case State::ReadingBase8:         { throw JsonFormatException("0-7", "0", "Unexpected End of String"); }
    case State::ReadingBase10:        { throw JsonFormatException("0-9", "numeric value", "Unexpected End of String"); }
    case State::ReadingBase16:        { throw JsonFormatException("0-9/a-f/A-F", "0x/0X", "Unexpected End of String"); }
    case State::ReadingBoolValue:     { throw JsonFormatException("true/True/false/False", "t/f/T/F", "Unexpected End of String"); }
    case State::ExpectingPSeparator:  { throw JsonFormatException(",", "value", "Unexpected End of String"); }
  }

  // unlikely to be reached 
  return length;
}


inline auto __dumpIndented( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    JsonObject const& object,
    Size              indent, // NOLINT(bugprone-easily-swappable-parameters)
    Size              depth   // NOLINT(bugprone-easily-swappable-parameters)
) noexcept -> String {
  using namespace cds::literals;
  String const indentation        = " "_s * (indent * depth);           // NOLINT(cppcoreguidelines-init-variables)
  String const futureIndentation  = indentation + " "_s * indent; // NOLINT(cppcoreguidelines-init-variables)

  String result = "{\n"; // NOLINT(cppcoreguidelines-init-variables) 
  for (auto const& element : object) {
    result += futureIndentation + __dumpIndented(element, indent, depth + 1) + ",\n";
  }

  if (object.empty()) {
    return "{}";
  }
  return result.replace(static_cast<Index>(result.size()) - 2, static_cast<Index>(result.size()), "\n") + indentation + "}";
}


inline auto __dumpIndented( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    JsonArray const&  array,
    Size              indent, // NOLINT(bugprone-easily-swappable-parameters)
    Size              depth   // NOLINT(bugprone-easily-swappable-parameters)
) noexcept -> String {
  using namespace cds::literals;
  String const indentation        = " "_s * (indent * depth);           // NOLINT(cppcoreguidelines-init-variables)
  String const futureIndentation  = indentation + " "_s * indent; // NOLINT(cppcoreguidelines-init-variables)

  String result = "[\n"; // NOLINT(cppcoreguidelines-init-variables) 
  for (auto const& element : array) {
    result += futureIndentation + __dumpIndented(element, indent, depth + 1) + ",\n";
  }

  if (array.empty()) {
    return "[]";
  }

  return result.replace(static_cast<Index>(result.size()) - 2, static_cast<Index>(result.size()), "\n") + indentation + "]";
}


inline auto __escape(String const& string) noexcept -> String {
  String newStr = "";
  for (auto c : string) {
    if (c == '\n') {
      newStr += "\\n";
    } else if (c == '\t') {
      newStr += "\\t";
    } else if (c == '\f') {
      newStr += "\\f";
    } else if (c == '\r') {
      newStr += "\\r";
    } else if (c == '\v') {
      newStr += "\\v";
    } else if (c == '\a') {
      newStr += "\\a";
    } else if (c == '\b') {
      newStr += "\\b";
    } else if (c == '\"') {
      newStr += "\\\"";
    } else {
      newStr += c;
    }
  }

  return newStr;
}


inline auto __dumpIndented( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    JsonElement const&  object,
    Size                indent, // NOLINT(bugprone-easily-swappable-parameters)
    Size                depth   // NOLINT(bugprone-easily-swappable-parameters)
) noexcept -> String {
  if (object.isJson()) { // NOLINT(bugprone-branch-clone) 
    return __dumpIndented(object.getJson(), indent, depth);
  } else if (object.isArray()) {
    return __dumpIndented(object.getArray(), indent, depth);
  } else {
    return object.toString();
  }
}


inline auto __dumpIndented( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    MapEntry<String, JsonElement> const&  entry,
    Size                                  indent, // NOLINT(bugprone-easily-swappable-parameters)
    Size                                  depth   // NOLINT(bugprone-easily-swappable-parameters)
) noexcept -> String {
  using namespace cds::literals;
  String common = R"(")" + entry.key() + "\" : "; // NOLINT(cppcoreguidelines-init-variables)
  if (entry.value().isJson()) { // NOLINT(bugprone-branch-clone) 
    return common + "\n" + (" "_s * (indent * depth)) + __dumpIndented(entry.value().getJson(), indent, depth);
  } else if (entry.value().isArray()) {
    return common + "\n" + (" "_s * (indent * depth)) + __dumpIndented(entry.value().getArray(), indent, depth);
  } else {
    return common + entry.value().toString();
  }
}
} // namespace __impl 
} // namespace __hidden 

inline auto JsonElement::copyData(__GenericData const& data) noexcept(false) -> void {
  switch (this->_type) {
    case __hidden::__impl::__JsonElementType::__jet_Object: {
      this->_data.data().pObject = new JsonObject(*static_cast<JsonObject const*>(data.pObject));
      break;
    }

    case __hidden::__impl::__JsonElementType::__jet_Array: {
      this->_data.data().pObject = new JsonArray(*static_cast<JsonArray const*>(data.pObject));
      break;
    }

    case __hidden::__impl::__JsonElementType::__jet_String: {
      this->_data.data().pObject = new String(*static_cast<String const*>(data.pObject));
      break;
    }

    case __hidden::__impl::__JsonElementType::__jet_Bool:
    case __hidden::__impl::__JsonElementType::__jet_Long:
    case __hidden::__impl::__JsonElementType::__jet_Double: {
      (void) std::memcpy(
          static_cast<void*>(&this->_data._data[0U]),
          static_cast<void const*>(&data),
          sizeof(__GenericData)
      );
      break;
    }

    case __hidden::__impl::__JsonElementType::__jet_Invalid:
    default: {
      break;
    }
  }
}

inline auto JsonElement::moveData(__GenericData& data) noexcept -> void {
  (void) std::memcpy(
      static_cast<void*>(&this->_data._data[0U]),
      static_cast<void const*>(&data),
      sizeof(__GenericData)
  );

  (void) std::memset(static_cast<void*>(&data), 0U, sizeof(__GenericData));
}

inline auto JsonElement::clearData() noexcept -> void {
  if (
      this->_type == json::__hidden::__impl::__JsonElementType::__jet_Object
      || this->_type == json::__hidden::__impl::__JsonElementType::__jet_String
      || this->_type == json::__hidden::__impl::__JsonElementType::__jet_Array
  ) {
    delete this->_data.data().pObject;
  }

  (void) std::memset(static_cast<void*>(&this->_data._data[0U]), 0U, sizeof(__GenericData));
}

inline JsonElement::JsonElement(JsonElement const& element) noexcept(false) : _type(element._type) {
  this->copyData(element._data.data());
}

inline JsonElement::JsonElement(JsonElement&& element) noexcept :
    _type(cds::exchange(element._type, __hidden::__impl::__JsonElementType::__jet_Invalid)) {
  this->moveData(element._data.data());
}

template <
    typename __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf<__hidden::__impl::__JsonElementPrimitiveAdaptable<__Element>::value>
> inline JsonElement::JsonElement(__Element value) noexcept(false) :
    _type(__hidden::__impl::__JsonElementAdapterProperties<__Element>::__type) {
  *static_cast<typename __hidden::__impl::__JsonElementAdapterProperties<__Element>::__AdaptedType*>(
      static_cast<void*> (&this->_data._data[0U])
  ) = value;
}

template <
    typename __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf<__hidden::__impl::__JsonElementAdaptable<__Element>::value>
> inline JsonElement::JsonElement(__Element&& value) noexcept(false) :
    _type(__hidden::__impl::__JsonElementAdapterProperties<__Element>::__type) {
  this->_data.data().pObject =
      new typename __hidden::__impl::__JsonElementAdapterProperties<__Element>::__AdaptedType(
          std::forward<__Element>(value)
      );
}

inline JsonElement::~JsonElement() noexcept { 
  this->clearData(); 
}

inline auto JsonElement::operator=(JsonElement const& element) noexcept(false) -> JsonElement& {
  if (this == &element) { 
    return *this; 
  }

  this->clearData();
  this->_type = element._type;
  this->copyData(element._data.data());
  return *this;
}

inline auto JsonElement::operator=(JsonElement&& element) noexcept -> JsonElement& {
  if (this == &element) { 
    return *this; 
  }

  this->clearData();
  this->_type = cds::exchange(element._type, json::__hidden::__impl::__JsonElementType::__jet_Invalid);
  this->moveData(element._data.data());
  return *this;
}

template <  
    typename __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf<__hidden::__impl::__JsonElementPrimitiveAdaptable<__Element>::value>
> inline auto JsonElement::operator=(__Element value) noexcept(false) -> JsonElement& {
  this->clearData();
  this->_type = __hidden::__impl::__JsonElementAdapterProperties<__Element>::__type;
  *static_cast<typename __hidden::__impl::__JsonElementAdapterProperties<__Element>::__AdaptedType*>(
      static_cast <void*> (&this->_data._data[0U])
  ) = value;

  return *this;
}

template <
    typename __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf<__hidden::__impl::__JsonElementAdaptable<__Element>::value>
> inline auto JsonElement::operator=(__Element&& value) noexcept(false) -> JsonElement& {
  this->clearData();
  this->_type = __hidden::__impl::__JsonElementAdapterProperties<__Element>::__type;
  this->_data.data().pObject =
      new typename __hidden::__impl::__JsonElementAdapterProperties<__Element>::__AdaptedType(
          std::forward<__Element>(value)
      );
  return *this;
}

inline auto JsonElement::toString() const noexcept -> String {
  switch (this->_type) {
    case __hidden::__impl::__JsonElementType::__jet_Object:
    case __hidden::__impl::__JsonElementType::__jet_Array: {
      return this->_data.data().pObject->toString();
    }

    case __hidden::__impl::__JsonElementType::__jet_String: {
      return "\"" + __hidden::__impl::__escape(this->_data.data().pObject->toString()) + "\"";
    }

    case __hidden::__impl::__JsonElementType::__jet_Bool: {
      return this->_data.data().bValue ? "true" : "false";
    }

    case __hidden::__impl::__JsonElementType::__jet_Long: {
      return this->_data.data().iValue;
    }

    case __hidden::__impl::__JsonElementType::__jet_Double: {
      return this->_data.data().dValue;
    }

    case __hidden::__impl::__JsonElementType::__jet_Invalid:
    default: {
      return "Invalid";
    }
  }
}

inline auto JsonElement::hash() const noexcept -> Size {
  switch (this->_type) {
    case __hidden::__impl::__JsonElementType::__jet_Object:
    case __hidden::__impl::__JsonElementType::__jet_Array: {
      return this->_data.data().pObject->hash();
    }

    case __hidden::__impl::__JsonElementType::__jet_Bool: {
      return cds::Hash<bool>::hash(this->_data.data().bValue);
    }

    case __hidden::__impl::__JsonElementType::__jet_Long: {
      return cds::Hash<long long int>::hash(this->_data.data().iValue);
    }

    case __hidden::__impl::__JsonElementType::__jet_Double: {
      return cds::Hash<double>::hash(this->_data.data().dValue);
    }

    case __hidden::__impl::__JsonElementType::__jet_Invalid:
    default: {
      return 0u;
    }
  }
}

inline auto JsonElement::equals(Object const& object) const noexcept -> bool {
  if (this == &object) { 
    return true; 
  }

  auto pJsonElement = dynamic_cast<decltype(this)>(&object);
  if (pJsonElement == nullptr) { 
    return false; 
  }

  if (this->_type != pJsonElement->_type) { 
    return false; 
  }

  if (
      this->_type == json::__hidden::__impl::__JsonElementType::__jet_Object
      || this->_type == json::__hidden::__impl::__JsonElementType::__jet_Array
      || this->_type == json::__hidden::__impl::__JsonElementType::__jet_String
  ) {

    return this->_data.data().pObject->equals(*pJsonElement->_data.data().pObject);
  }

  return 0 == std::memcmp(
      static_cast<void const*>(&this->_data._data[0U]),
      static_cast<void const*>(&pJsonElement->_data._data[0U]),
      sizeof(__GenericData)
  );
}

inline auto JsonElement::getInt() const noexcept(false) -> int {
  if (this->_type != __hidden::__impl::__JsonElementType::__jet_Int) {
    throw TypeException(String::f(
        "Type Cast Exception. Cannot convert '%s' to '%s'",
        __hidden::__impl::__jet_toString(this->_type), "int"
    ));
  }
  return static_cast<int>(this->_data.data().iValue);
}

inline auto JsonElement::getLong() const noexcept(false) -> long long int {
  if (this->_type != __hidden::__impl::__JsonElementType::__jet_Long) {
    throw TypeException(String::f(
        "Type Cast Exception. Cannot convert '%s' to '%s'",
        __hidden::__impl::__jet_toString(this->_type), "long"
    ));
  }
  return this->_data.data().iValue;
}

inline auto JsonElement::getFloat() const noexcept(false) -> float {
  if (this->_type != __hidden::__impl::__JsonElementType::__jet_Float) {
    throw TypeException(String::f(
        "Type Cast Exception. Cannot convert '%s' to '%s'",
        __hidden::__impl::__jet_toString(this->_type), "float"
    ));
  }
  return static_cast<float>(this->_data.data().dValue);
}

inline auto JsonElement::getDouble() const noexcept(false) -> double {
  if (this->_type != __hidden::__impl::__JsonElementType::__jet_Double) {
    throw TypeException(String::f(
        "Type Cast Exception. Cannot convert '%s' to '%s'",
        __hidden::__impl::__jet_toString(this->_type), "double"
    ));
  }

  return this->_data.data().dValue;
}

inline auto JsonElement::getBoolean() const noexcept(false) -> bool {
  if (this->_type != __hidden::__impl::__JsonElementType::__jet_Bool) {
    throw TypeException(String::f(
        "Type Cast Exception. Cannot convert '%s' to '%s'",
        __hidden::__impl::__jet_toString(this->_type), "bool"
    ));
  }

  return this->_data.data().bValue;
}

inline auto JsonElement::getString() const noexcept(false) -> String const& {
  if (this->_type != __hidden::__impl::__JsonElementType::__jet_String) {
    throw TypeException(String::f(
        "Type Cast Exception. Cannot convert '%s' to '%s'",
        __hidden::__impl::__jet_toString(this->_type), "String"
    ));
  }
  return *static_cast<String const*>(this->_data.data().pObject);
}

inline auto JsonElement::getJson() const noexcept(false) -> JsonObject const& {
  if (this->_type != __hidden::__impl::__JsonElementType::__jet_Object) {
    throw TypeException(String::f(
        "Type Cast Exception. Cannot convert '%s' to '%s'",
        __hidden::__impl::__jet_toString(this->_type), "JsonObject")
    );
  }
  return *static_cast<JsonObject const*>(this->_data.data().pObject);
}

inline auto JsonElement::getArray() const noexcept(false) -> JsonArray const& {
  if (this->_type != __hidden::__impl::__JsonElementType::__jet_Array) {
    throw TypeException(String::f(
        "Type Cast Exception. Cannot convert '%s' to '%s'",
        __hidden::__impl::__jet_toString(this->_type), "JsonArray"
    ));
  }
  return *static_cast<JsonArray const*>(this->_data.data().pObject);
}

inline auto JsonElement::getString() noexcept(false) -> String& {
  if (this->_type != __hidden::__impl::__JsonElementType::__jet_String) {
    throw TypeException(String::f(
        "Type Cast Exception. Cannot convert '%s' to '%s'",
        __hidden::__impl::__jet_toString(this->_type), "String"
    ));
  }
  return *static_cast<String*>(this->_data.data().pObject);
}

inline auto JsonElement::getJson() noexcept(false) -> JsonObject& {
  if (this->_type != __hidden::__impl::__JsonElementType::__jet_Object) {
    throw TypeException(String::f(
        "Type Cast Exception. Cannot convert '%s' to '%s'",
        __hidden::__impl::__jet_toString(this->_type), "JsonObject"
    ));
  }
  return *static_cast<JsonObject*>(this->_data.data().pObject);
}

inline auto JsonElement::getArray() noexcept(false) -> JsonArray& {
  if (this->_type != __hidden::__impl::__JsonElementType::__jet_Array) {
    throw TypeException(String::f(
        "Type Cast Exception. Cannot convert '%s' to '%s'",
        __hidden::__impl::__jet_toString(this->_type), "JsonArray"
    ));
  }

  return *static_cast<JsonArray*>(this->_data.data().pObject);
}

constexpr JsonObject::JsonObject() noexcept = default;

inline JsonObject::JsonObject(JsonObject const& object) noexcept(false) : __Base(static_cast<__Base const&>(object)) {}

constexpr JsonObject::JsonObject(JsonObject&& object) noexcept : __Base(static_cast<__Base&&>(std::move(object))) {}

inline JsonObject::JsonObject(Map<String, JsonElement> const& map) noexcept(false) : __Base(map) {}

inline JsonObject::JsonObject(StringView asString) noexcept(false) {
  for (Size index = 0u; index < asString.length(); ++index) {
    if (asString[index] == '{') {
      __hidden::__impl::__parseJsonObject(asString, index + 1u, asString.length(), *this);
      break;
    }
  }
}

inline JsonObject::~JsonObject() noexcept = default;

inline auto JsonObject::operator=(JsonObject const& object) noexcept(false) -> JsonObject& {
  if (this == &object) {
    return *this;
  }
  this->__Base::operator=(static_cast<__Base const&>(object));
  return *this;
}

inline auto JsonObject::operator=(JsonObject&& object) noexcept -> JsonObject& {
  if (this == &object) {
    return *this;
  }

  this->__Base::operator=(static_cast<__Base&&>(std::move(object)));
  return *this;
}

inline auto JsonObject::operator=(Map<String, JsonElement> const& map) noexcept(false) -> JsonObject& {
  if (this == &map) {
    return *this;
  }

  this->__Base::operator=(map);
  return *this;
}

template <typename __Element> inline auto JsonObject::put(StringView label, __Element&& value) noexcept -> JsonObject& {
  (void) this->emplace(label, std::forward<__Element>(value));
  return *this;
}

inline auto JsonObject::get(StringView label) noexcept(false) -> JsonElement& {
  return this->at(label);
}

inline auto JsonObject::get(StringView label) const noexcept(false) -> JsonElement const& {
  return this->at(label);
}

inline auto JsonObject::operator[](StringView label) noexcept(false) -> JsonElement& {
  return this->at(label);
}

inline auto JsonObject::getInt(StringView label) const noexcept(false) -> int {
  auto elementIterator =
      this->findFirstThat([label](MapEntry<String, JsonElement> const& entry) { return entry.key() == label; });

  if (elementIterator == this->end()) {
    throw KeyException(label);
  }

  return elementIterator->value().getInt();
}


inline auto JsonObject::getLong(StringView label) const noexcept(false) -> long long int {
  auto elementIterator =
      this->findFirstThat([label](MapEntry<String, JsonElement> const& entry) { return entry.key() == label; });

  if (elementIterator == this->end()) {
    throw KeyException(label);
  }

  return elementIterator->value().getLong();
}


inline auto JsonObject::getFloat(StringView label) const noexcept(false) -> float {
  auto elementIterator =
      this->findFirstThat([label](MapEntry<String, JsonElement> const& entry) { return entry.key() == label; });

  if (elementIterator == this->end()) {
    throw KeyException(label);
  }

  return elementIterator->value().getFloat();
}


inline auto JsonObject::getDouble(StringView label) const noexcept(false) -> double {
  auto elementIterator =
      this->findFirstThat([label](MapEntry<String, JsonElement> const& entry) { return entry.key() == label; });

  if (elementIterator == this->end()) {
    throw KeyException(label);
  }

  return elementIterator->value().getDouble();
}


inline auto JsonObject::getBoolean(StringView label) const noexcept(false) -> bool {
  auto elementIterator =
      this->findFirstThat([label](MapEntry<String, JsonElement> const& entry) { return entry.key() == label; });

  if (elementIterator == this->end()) {
    throw KeyException(label);
  }

  return elementIterator->value().getBoolean();
}


inline auto JsonObject::getString(StringView label) const noexcept(false) -> String const& {
  auto elementIterator =
      this->findFirstThat([label](MapEntry<String, JsonElement> const& entry) { return entry.key() == label; });

  if (elementIterator == this->end()) {
    throw KeyException(label);
  }

  return elementIterator->value().getString();
}


inline auto JsonObject::getArray(StringView label) const noexcept(false) -> JsonArray const& {
  auto elementIterator =
      this->findFirstThat([label](MapEntry<String, JsonElement> const& entry) { return entry.key() == label; });

  if (elementIterator == this->end()) {
    throw KeyException(label);
  }

  return elementIterator->value().getArray();
}


inline auto JsonObject::getJson(StringView label) const noexcept(false) -> JsonObject const& {
  auto elementIterator =
      this->findFirstThat([label](MapEntry<String, JsonElement> const& entry) { return entry.key() == label; });

  if (elementIterator == this->end()) {
    throw KeyException(label);
  }

  return elementIterator->value().getJson();
}


inline auto JsonObject::getString(StringView label) noexcept(false) -> String& {
  auto elementIterator =
      this->findFirstThat([label](MapEntry<String, JsonElement> const& entry) { return entry.key() == label; });

  if (elementIterator == this->end()) {
    throw KeyException(label);
  }

  return elementIterator->value().getString();
}


inline auto JsonObject::getArray(StringView label) noexcept(false) -> JsonArray& {
  auto elementIterator =
      this->findFirstThat([label](MapEntry<String, JsonElement> const& entry) { return entry.key() == label; });

  if (elementIterator == this->end()) {
    throw KeyException(label);
  }

  return elementIterator->value().getArray();
}


inline auto JsonObject::getJson(StringView label) noexcept(false) -> JsonObject& {
  auto elementIterator =
      this->findFirstThat([label](MapEntry<String, JsonElement> const& entry) { return entry.key() == label; });

  if (elementIterator == this->end()) {
    throw KeyException(label);
  }

  return elementIterator->value().getJson();
}

constexpr JsonArray::JsonArray() noexcept = default;

inline JsonArray::JsonArray(JsonArray const& array) noexcept(false) : __Base(static_cast<__Base const&>(array)) {}

constexpr JsonArray::JsonArray(JsonArray&& array) noexcept : __Base(static_cast<__Base&&>(std::move(array))) {}

inline JsonArray::JsonArray(List<JsonElement> const& list) noexcept(false) : __Base(list) {}

inline JsonArray::JsonArray(StringView asString) noexcept(false) {
  for (Size index = 0u; index < asString.length(); ++index) {
    if (asString[index] == '[') {
      __hidden::__impl::__parseJsonArray(asString, index + 1u, asString.length(), *this);
      break;
    }
  }
}

inline JsonArray::~JsonArray() noexcept = default;

inline auto JsonArray::operator=(JsonArray const& array) noexcept(false) -> JsonArray& {
  if (this == &array) {
    return *this;
  }

  this->__Base::operator=(static_cast<__Base const&>(array));
  return *this;
}

inline auto JsonArray::operator=(JsonArray&& array) noexcept -> JsonArray& {
  if (this == &array) {
    return *this;
  }

  this->__Base::operator=(static_cast<__Base&&>(std::move(array)));
  return *this;
}

inline auto JsonArray::operator=(List<JsonElement> const& list) noexcept(false) -> JsonArray& {
  if (this == &list) {
    return *this;
  }

  this->__Base::operator=(list);
  return *this;
}

template <typename __Element> inline auto JsonArray::pushBack(__Element&& value) noexcept(false) -> JsonArray& {
  (void) this->emplaceBack(std::forward<__Element>(value));
  return *this;
}

template <typename __Element> inline auto JsonArray::pushFront(__Element&& value) noexcept(false) -> JsonArray& {
  (void) this->emplaceFront(std::forward<__Element>(value));
  return *this;
}

inline auto JsonArray::getInt(Index index) const noexcept(false) -> int {
  return this->get(index).getInt();
}

inline auto JsonArray::getLong(Index index) const noexcept(false) -> long long int {
  return this->get(index).getLong();
}

inline auto JsonArray::getFloat(Index index) const noexcept(false) -> float {
  return this->get(index).getFloat();
}

inline auto JsonArray::getDouble(Index index) const noexcept(false) -> double {
  return this->get(index).getDouble();
}

inline auto JsonArray::getBoolean(Index index) const noexcept(false) -> bool {
  return this->get(index).getBoolean();
}

inline auto JsonArray::getString(Index index) const noexcept(false) -> String const& {
  return this->get(index).getString();
}

inline auto JsonArray::getArray(Index index) const noexcept(false) -> JsonArray const& {
  return this->get(index).getArray();
}

inline auto JsonArray::getJson(Index index) const noexcept(false) -> JsonObject const& {
  return this->get(index).getJson();
}

inline auto JsonArray::getString(Index index) noexcept(false) -> String& {
  return this->get(index).getString();
}

inline auto JsonArray::getArray(Index index) noexcept(false) -> JsonArray& {
  return this->get(index).getArray();
}

inline auto JsonArray::getJson(Index index) noexcept(false) -> JsonObject& {
  return this->get(index).getJson();
}

inline auto parseJson(StringView asString) noexcept(false) -> JsonObject {
  return JsonObject(asString);
}

inline auto parseJsonArray(StringView asString) noexcept(false) -> JsonArray {
  return JsonArray(asString);
}

__CDS_NoDiscard inline auto dump(JsonObject const& object, Size indent) noexcept -> String {
  return __hidden::__impl::__dumpIndented(object, indent, 0);
}

__CDS_NoDiscard inline auto dump(JsonArray const& object, Size indent) noexcept -> String {
  return __hidden::__impl::__dumpIndented(object, indent, 0);
}


inline auto JsonObject::toString() const noexcept -> String {
  if (this->empty()) {
    return "{}";
  }

  std::stringstream oss;
  oss << "{ ";
  for (auto iterator = this->begin(), end = this->end(); iterator != end; ++iterator) {
    cds::meta::print(cds::meta::print(oss << '"', (*iterator).key()) << "\": ", (*iterator).value()) << ", ";
  }

  auto asString = oss.str();
  asString[asString.length() - 2U] = ' ';
  asString[asString.length() - 1U] = '}';
  return asString;
}

} // namespace json 
} // namespace cds 

#endif // __CDS_JSON_IMPL_HPP__
