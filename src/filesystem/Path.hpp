//
// Created by loghin on 19.04.2025.
//

#ifndef CDS_FILESYSTEM_PATH_HPP
#define CDS_FILESYSTEM_PATH_HPP
#pragma once

#include "Path.hpp"

#include <cds/meta/Compiler>
#include <cds/meta/Platform>
#include <cds/String>
#include <cds/StringView>

#if CDS_ATTR(os_win32)
#include <windows.h>
#include <cds/collection/Vector>
#else
#include <sys/stat.h>
#endif

namespace cds {
namespace filesystem {
namespace impl {
using cds::impl::mv;

template <typename> struct PathUtilsConstants {};

template <typename = void> struct PathUtilsCharConstants {
  static char constexpr portableSeparator = '/';
  static char constexpr win32Separator = '\\';
  static char constexpr dot = '.';

#if CDS_ATTR(os_win32)
  static char constexpr nativeSeparator = win32Separator;
  static char constexpr nonNativeSeparator = portableSeparator;
#else
  static char constexpr nativeSeparator = portableSeparator;
  static char constexpr nonNativeSeparator = win32Separator;
#endif
};

template <typename = void> struct PathUtilsWCharConstants {
  static wchar_t constexpr portableSeparator = L'/';
  static wchar_t constexpr win32Separator = L'\\';
  static wchar_t constexpr dot = L'.';

#if CDS_ATTR(os_win32)
  static wchar_t constexpr nativeSeparator = win32Separator;
  static wchar_t constexpr nonNativeSeparator = portableSeparator;
#else
  static wchar_t constexpr nativeSeparator = portableSeparator;
  static wchar_t constexpr nonNativeSeparator = win32Separator;
#endif
};

template <typename = void> struct PathUtilsChar16Constants {
  static char16_t constexpr portableSeparator = u'/';
  static char16_t constexpr win32Separator = u'\\';
  static char16_t constexpr dot = u'.';

#if CDS_ATTR(os_win32)
  static char16_t constexpr nativeSeparator = win32Separator;
  static char16_t constexpr nonNativeSeparator = portableSeparator;
#else
  static char16_t constexpr nativeSeparator = portableSeparator;
  static char16_t constexpr nonNativeSeparator = win32Separator;
#endif
};

template <typename = void> struct PathUtilsChar32Constants {
  static char32_t constexpr portableSeparator = U'/';
  static char32_t constexpr win32Separator = U'\\';
  static char32_t constexpr dot = U'.';

#if CDS_ATTR(os_win32)
  static char32_t constexpr nativeSeparator = win32Separator;
  static char32_t constexpr nonNativeSeparator = portableSeparator;
#else
  static char32_t constexpr nativeSeparator = portableSeparator;
  static char32_t constexpr nonNativeSeparator = win32Separator;
#endif
};

#if CDS_ATTR(cpp20)
template <typename = void> struct PathUtilsChar8Constants {
  static char8_t constexpr portableSeparator = u8'/';
  static char8_t constexpr win32Separator = u8'\\';
  static char8_t constexpr dot = u8'.';

#if CDS_ATTR(os_win32)
  static char8_t constexpr nativeSeparator = win32Separator;
  static char8_t constexpr nonNativeSeparator = portableSeparator;
#else
  static char8_t constexpr nativeSeparator = portableSeparator;
  static char8_t constexpr nonNativeSeparator = win32Separator;
#endif
};
#endif

template <typename T> char const PathUtilsCharConstants<T>::portableSeparator;
template <typename T> char const PathUtilsCharConstants<T>::win32Separator;
template <typename T> char const PathUtilsCharConstants<T>::nativeSeparator;
template <typename T> char const PathUtilsCharConstants<T>::nonNativeSeparator;
template <typename T> char const PathUtilsCharConstants<T>::dot;

template <typename T> wchar_t const PathUtilsWCharConstants<T>::portableSeparator;
template <typename T> wchar_t const PathUtilsWCharConstants<T>::win32Separator;
template <typename T> wchar_t const PathUtilsWCharConstants<T>::nativeSeparator;
template <typename T> wchar_t const PathUtilsWCharConstants<T>::nonNativeSeparator;
template <typename T> wchar_t const PathUtilsWCharConstants<T>::dot;

template <typename T> char16_t const PathUtilsChar16Constants<T>::portableSeparator;
template <typename T> char16_t const PathUtilsChar16Constants<T>::win32Separator;
template <typename T> char16_t const PathUtilsChar16Constants<T>::nativeSeparator;
template <typename T> char16_t const PathUtilsChar16Constants<T>::nonNativeSeparator;
template <typename T> char16_t const PathUtilsChar16Constants<T>::dot;

template <typename T> char32_t const PathUtilsChar32Constants<T>::portableSeparator;
template <typename T> char32_t const PathUtilsChar32Constants<T>::win32Separator;
template <typename T> char32_t const PathUtilsChar32Constants<T>::nativeSeparator;
template <typename T> char32_t const PathUtilsChar32Constants<T>::nonNativeSeparator;
template <typename T> char32_t const PathUtilsChar32Constants<T>::dot;

#if CDS_ATTR(cpp20)
template <typename T> char8_t const PathUtilsChar8Constants<T>::portableSeparator;
template <typename T> char8_t const PathUtilsChar8Constants<T>::win32Separator;
template <typename T> char8_t const PathUtilsChar8Constants<T>::nativeSeparator;
template <typename T> char8_t const PathUtilsChar8Constants<T>::nonNativeSeparator;
template <typename T> char8_t const PathUtilsChar8Constants<T>::dot;
#endif

template <> struct PathUtilsConstants<char> : PathUtilsCharConstants<> {};
template <> struct PathUtilsConstants<wchar_t> : PathUtilsWCharConstants<> {};
template <> struct PathUtilsConstants<char16_t> : PathUtilsChar16Constants<> {};
template <> struct PathUtilsConstants<char32_t> : PathUtilsChar32Constants<> {};
#if CDS_ATTR(cpp20)
template <> struct PathUtilsConstants<char8_t> : PathUtilsChar8Constants<> {};
#endif

#if CDS_ATTR(os_win32)
using PathNativeType = cds::impl::BaseString<wchar_t>;
using PathNativeViewType = cds::impl::BaseStringView<wchar_t>;
using PathNativeConstants = PathUtilsConstants<wchar_t>;
#else
using PathNativeType = cds::impl::BaseString<char>;
using PathNativeViewType = cds::impl::BaseStringView<char>;
using PathNativeConstants = PathUtilsConstants<char>;
#endif

enum class PathFormat {
  Native,
  Portable,
  AsIs
};

class PathIterator;

class Path {
public:
  using NativeString = PathNativeType;
  using NativeStringView = PathNativeViewType;
  using Constants = PathNativeConstants;
  using Format = PathFormat;

  Path() noexcept = default;
  Path(Path const&) noexcept = default;
  Path(Path&&) noexcept = default;

  CDS_ATTR(implicit) Path(NativeString&& str, Format const format = Format::Native) noexcept : _base{mv(str)} {
    if (format == Format::Native) {
      toNative(_base);
    } else if (format == Format::Portable) {
      toPortable(_base);
    }
  }

  template <typename S> CDS_ATTR(implicit) Path(S const& str, Format const format = Format::Native) noexcept :
      Path{NativeString{str}, format} {}

  template <typename I, typename S> Path(I begin, S end, Format const format = Format::Native) noexcept :
      Path{NativeString{begin, end}, format} {}

  ~Path() noexcept = default;

  auto operator=(Path const&) noexcept -> Path& = default;
  auto operator=(Path&&) noexcept -> Path& = default;

  auto operator=(NativeString&& str) noexcept -> Path& {
    return assign(mv(str));
  }

  template <typename S> auto operator=(S const& str) noexcept -> Path& {
    return assign(str);
  }

  auto assign(NativeString&& str, Format const format = Format::Native) noexcept -> Path& {
    _base = mv(str);
    if (format == Format::Native) {
      toNative(_base);
    } else if (format == Format::Portable) {
      toPortable(_base);
    }

    return *this;
  }

  template <typename S> auto assign(S const& str, Format const format = Format::Native) noexcept -> Path& {
    return assign(NativeString{str}, format);
  }

  template <typename I, typename S> auto assign(I begin, S end, Format const format = Format::Native) noexcept -> Path& {
    return assign(NativeString{begin, end}, format);
  }

  auto operator/=(Path const& path) noexcept -> Path& {
    return append(path);
  }

  auto operator/=(Path&& path) noexcept -> Path& {
    return append(mv(path));
  }

  template <typename S> auto operator/=(S const& str) noexcept -> Path& {
    return append(str);
  }

  auto operator+=(Path const& path) noexcept -> Path& {
    return concat(path);
  }

  auto operator+=(Path&& path) noexcept -> Path& {
    return concat(mv(path));
  }

  template <typename S> auto operator+=(S const& str) noexcept -> Path& {
    return concat(str);
  }

  auto append(Path const& path) noexcept -> Path& {
    if (!_base.empty() && _base.back() != Constants::nativeSeparator) {
      _base += Constants::nativeSeparator;
    }
    auto offset = 0;
    while (offset < path._base.length() && path._base[offset] == Constants::nativeSeparator) {
      ++offset;
    }
    if (offset != 0) {
      return concat(path._base.sub(offset));
    }

    return concat(path);
  }

  auto append(Path&& path) noexcept -> Path& {
    if (!_base.empty() && _base.back() != Constants::nativeSeparator) {
      _base += Constants::nativeSeparator;
    }
    auto offset = 0;
    while (offset < path._base.length() && path._base[offset] == Constants::nativeSeparator) {
      ++offset;
    }
    if (offset != 0) {
      path._base = path._base.sub(offset);
    }

    return concat(mv(path));
  }

  auto append(NativeString&& str, Format const format = Format::Native) noexcept -> Path& {
    if (!_base.empty() && _base.back() != Constants::nativeSeparator) {
      _base += Constants::nativeSeparator;
    }
    auto offset = 0;
    while (offset < str.length() && str[offset] == Constants::nativeSeparator) {
      ++offset;
    }
    if (offset != 0) {
      str = str.sub(offset);
    }

    return concat(mv(str), format);
  }

  template <typename S> auto append(S const& str, Format const format = Format::Native) noexcept -> Path& {
    return append(NativeString{str}, format);
  }

  template <typename I, typename S> auto append(I begin, S end, Format const format = Format::Native) noexcept -> Path& {
    return append(NativeString{begin, end}, format);
  }

  auto concat(Path const& path) noexcept -> Path& {
    _base += path._base;
    return *this;
  }

  auto concat(Path&& path) noexcept -> Path& {
    _base += mv(path._base);
    return *this;
  }

  auto concat(NativeString&& path, Format const format = Format::Native) noexcept -> Path& {
    if (format == Format::Native) {
      toNative(path);
    } else if (format == Format::Portable) {
      toPortable(path);
    }

    _base += mv(path);
    return *this;
  }

  template <typename S> auto concat(S const& str, Format const format = Format::Native) noexcept -> Path& {
    return concat(NativeString{str}, format);
  }

  template <typename I, typename S> auto concat(I begin, S end, Format const format = Format::Native) noexcept -> Path& {
    return concat(NativeString{begin, end}, format);
  }

  auto clear() noexcept -> void {
    _base.clear();
  }

  auto removeFilename() noexcept -> Path& {
    auto pos = _base.findLast(Constants::nativeSeparator);
    if (pos != NativeString::npos) {
#if CDS_ATTR(os_linux) || CDS_ATTR(os_apple)
      if (pos == 0) {
        pos = 1;
      }
#endif
      _base = _base.sub(0, pos);
    } else {
      _base.clear();
    }
    return *this;
  }

  auto replaceFilename(Path const& path) noexcept -> Path& {
    auto pos = _base.findLast(Constants::nativeSeparator);
    if (pos != NativeString::npos) {
      _base = mv(_base).replace(pos + 1, _base.length(), path._base);
    } else {
      _base = path._base;
    }
    return *this;
  }

  template <typename S> auto replaceFilename(S const& str, Format const format = Format::Native) noexcept -> Path& {
    return replaceFilename(Path{str, format});
  }

  template <typename I, typename S> auto replaceFilename(I begin, S end, Format const format = Format::Native) noexcept
      -> Path& {
    return replaceFilename(Path{begin, end, format});
  }

  auto replaceExtension(NativeString&& str) noexcept -> Path& {
    auto const sepPos = _base.findLast(Constants::nativeSeparator);
    auto const extPos = _base.findLast(Constants::dot);

    if (sepPos != NativeString::npos && sepPos + 1 < extPos) {
      _base = _base.sub(0, extPos);
    }

    if (str.empty()) {
      return *this;
    }

    if (str.front() != Constants::dot) {
      _base += Constants::dot;
    }

    _base += mv(str);
    return *this;
  }

  template <typename S> auto replaceExtension(S const& str) noexcept -> Path& {
    return replaceExtension(NativeString{str});
  }

  template <typename I, typename S> auto replaceExtension(I begin, S end) noexcept -> Path& {
    return replaceExtension(NativeString{begin, end});
  }

  [[nodiscard]] auto root() const noexcept -> Path {
#if CDS_ATTR(os_linux) || CDS_ATTR(os_apple)
    if (_base.startsWith(Constants::nativeSeparator)) {
      return Path{_base.sub(0, 1)};
    }
    return Path{};
#elif CDS_ATTR(os_win32)
    if (_base.length() > 1 && _base[0] == Constants::nativeSeparator && _base[1] == Constants::nativeSeparator) {
      auto const mountPoint = _base.sub(2);
      auto const nextSep = mountPoint.findFirst(Constants::nativeSeparator);
      if (nextSep == NativeString::npos) {
        return *this;
      }

      return Path{_base.sub(0, nextSep)};
    }

    auto const nextSep = _base.findFirst(Constants::nativeSeparator);
    auto const potentialRoot = nextSep == NativeString::npos
        ? NativeStringView{_base}
        : _base.sub(0, nextSep);

    if (potentialRoot.length() != 2) {
      return Path{};
    }

    using Traits = typename NativeString::STraits;
    if (Traits::isUpper(potentialRoot[0]) && potentialRoot[1] == L':') {
      return potentialRoot;
    }
    return Path{};
#endif
  }

  [[nodiscard]] auto parent() const noexcept -> Path {
#if !CDS_ATTR(os_win32)
    if (_base == "/") {
      return *this;
    }
#endif
    auto const pos = _base.findLast(Constants::nativeSeparator);
    if (pos == NativeString::npos) {
      return Path{};
    }
#if !CDS_ATTR(os_win32)
    if (pos == 0) {
      return Path{_base.sub(0, 1)};
    }
#endif
    return Path{_base.sub(0, pos)};
  }

  [[nodiscard]] auto filename() const noexcept -> NativeStringView {
    auto const pos = _base.findLast(Constants::nativeSeparator);
    if (pos == NativeString::npos) {
      return _base;
    }
    return _base.sub(pos + 1);
  }

  [[nodiscard]] auto stem() const noexcept -> NativeStringView {
    auto const file = filename();
    auto const pos = file.findLast(Constants::dot);
    if (pos == 0 || pos + 1 == file.length()) {
      return file;
    }
    return file.sub(0, pos);
  }

  [[nodiscard]] auto extension() const noexcept -> NativeStringView {
    auto const file = filename();
    auto const pos = file.findLast(Constants::dot);
    if (pos == 0 || pos + 1 == file.length()) {
      return file.sub(0, 0);
    }
    return file.sub(pos);
  }

  [[nodiscard]] auto empty() const noexcept -> bool {
    return _base.empty();
  }

  [[nodiscard]] auto exists() const noexcept -> bool {
#if CDS_ATTR(os_win32)
    constexpr static auto initialResolvingBufferLength = 512u;
    wchar_t initialResolvingBuffer[initialResolvingBufferLength];
    auto const actualLength = GetFullPathNameW(
        _base.data(),
        initialResolvingBufferLength,
        initialResolvingBuffer,
        nullptr
    );

    if (actualLength == 0) {
      return false;
    }

    Vector<wchar_t> resolvingBuffer(actualLength);
    if (0 == GetFullPathNameW(
        _base.data(),
        actualLength,
        resolvingBuffer.data(),
        nullptr
    )) {
      return false;
    }
#elif CDS_ATTR(os_linux)
    struct stat64 fileStat{};
    if (0 != stat64(_base.data(), &fileStat)) {
      return false;
    }
#elif CDS_ATTR(os_apple)
    struct stat fileStat{};
    if (0 != stat(_base.data(), &fileStat)) {
      return false;
    }
#endif
    return true;
  }

  auto isRelative() const noexcept -> bool {
    return root().empty();
  }

  auto isAbsolute() const noexcept -> bool {
    return !root().empty();
  }

  auto isCanonical() const noexcept -> bool {
    if (!isAbsolute()) {
      return false;
    }

    auto const resolved = normalize(*this);
    if (resolved._base != _base) {
      return false;
    }

    return exists();
  }

  auto hasRoot() const noexcept -> bool {
    return !root().empty();
  }

  auto hasParent() const noexcept -> bool {
    if (parent().empty()) {
      return false;
    }

    return _base != root()._base;
  }

  auto hasFilename() const noexcept -> bool {
    return !filename().empty();
  }

  auto hasStem() const noexcept -> bool {
    return !stem().empty();
  }

  auto hasExtension() const noexcept -> bool {
    return !extension().empty();
  }

  auto str() const noexcept -> NativeStringView {
    return _base;
  }

  auto canonical() const noexcept -> Path;
  auto weaklyCanonical() const noexcept -> Path;
  auto normalized() const noexcept -> Path {
    return normalize(*this);
  }

  [[nodiscard]] auto begin() const noexcept -> PathIterator;
  [[nodiscard]] auto end() const noexcept -> PathIterator;
  [[nodiscard]] auto cbegin() const noexcept -> PathIterator;
  [[nodiscard]] auto cend() const noexcept -> PathIterator;

private:
  static auto toNative(NativeString& str) noexcept -> void {
    for (auto& c : str) {
      if (c == Constants::nonNativeSeparator) {
        c = Constants::nativeSeparator;
      }
    }
  }

  static auto toPortable(NativeString& str) noexcept -> void {
    for (auto& c : str) {
      if (c == Constants::win32Separator) {
        c = Constants::portableSeparator;
      }
    }
  }

  static auto normalize(Path const& src) noexcept -> Path;

  NativeString _base;
};

[[nodiscard]] inline auto operator/(Path const& lhs, Path const& rhs) noexcept -> Path {
  return Path{lhs}.append(rhs);
}

[[nodiscard]] inline auto operator/(Path const& lhs, Path&& rhs) noexcept -> Path {
  return Path{lhs}.append(mv(rhs));
}

template <typename S> auto operator/(Path const& lhs, S const& rhs) noexcept -> Path {
  return Path{lhs}.append(rhs);
}

[[nodiscard]] inline auto operator/(Path&& lhs, Path const& rhs) noexcept -> Path {
  return mv(lhs /= rhs);
}

[[nodiscard]] inline auto operator/(Path&& lhs, Path&& rhs) noexcept -> Path {
  return mv(lhs /= mv(rhs));
}

template <typename S> [[nodiscard]] auto operator/(Path&& lhs, S const& rhs) noexcept -> Path {
  return mv(lhs /= rhs);
}

inline auto operator<<(typename PathNativeType::OStream& out, Path const& obj) noexcept -> typename PathNativeType::OStream& {
  return out << obj.str();
}

class PathIterator {
public:
  using Constants = typename Path::Constants;
  using NativeStringView = typename Path::NativeStringView;

  PathIterator() noexcept = default;
  PathIterator(PathIterator const&) noexcept = default;
  PathIterator(PathIterator&&) noexcept = default;

  CDS_ATTR(explicit) PathIterator(Path const& path) noexcept {
    auto const str = path.str();
    auto const firstSep = str.findFirst(Constants::nativeSeparator);
    auto firstAfter = firstSep + 1;
    if (firstSep != NativeStringView::npos) {
      while (firstAfter < static_cast<Idx>(str.length()) && str[firstAfter] == Constants::nativeSeparator) {
        ++firstAfter;
      }
    }

#if CDS_ATTR(os_linux) || CDS_ATTR(os_apple)
    if (firstSep == 0) {
      _current = str.sub(0, 1);
      _rest = str.sub(firstAfter);
    } else
#endif
    if (firstSep == NativeStringView::npos) {
      _current = str;
    } else {
      _current = str.sub(0, firstSep);
      _rest = str.sub(firstAfter);
    }
  }

  ~PathIterator() noexcept = default;

  auto operator=(PathIterator const&) noexcept -> PathIterator& = default;
  auto operator=(PathIterator&&) noexcept -> PathIterator& = default;

  auto operator*() const noexcept -> NativeStringView {
    return _current;
  }

  auto operator++() noexcept -> PathIterator& {
    auto const firstSep = _rest.findFirst(Constants::nativeSeparator);
    auto firstAfter = firstSep + 1;
    if (firstSep != NativeStringView::npos) {
      while (firstAfter < static_cast<Idx>(_rest.length()) && _rest[firstAfter] == Constants::nativeSeparator) {
        ++firstAfter;
      }
    }

    if (firstSep == NativeStringView::npos) {
      _current = _rest;
      _rest = {};
    } else {
      _current = _rest.sub(0, firstSep);
      _rest = _rest.sub(firstAfter);
    }
    return *this;
  }

private:
  friend auto operator==(PathIterator const& lhs, PathIterator const& rhs) noexcept -> bool;
  friend auto operator!=(PathIterator const& lhs, PathIterator const& rhs) noexcept -> bool;

  NativeStringView _current {};
  NativeStringView _rest {};
};

inline auto Path::begin() const noexcept -> PathIterator {
  return PathIterator{*this};
}

inline auto Path::end() const noexcept -> PathIterator {
  return {};
}

inline auto Path::cbegin() const noexcept -> PathIterator {
  return PathIterator{*this};
}

inline auto Path::cend() const noexcept -> PathIterator {
  return {};
}

inline auto Path::normalize(Path const& src) noexcept -> Path {
  Path result;
  for (auto const& entry : src) {
    if (entry.length() == 1 && entry.front() == Constants::nativeSeparator && result.empty()) {
      result = entry;
      continue;
    }

    if (entry.length() == 1 && entry.front() == Constants::dot) {
      continue;
    }

    if (entry.length() == 2 && entry[0] == Constants::dot && entry[1] == Constants::dot) {
      auto prev = result.parent();
      if (prev._base == result._base && prev.hasRoot()) {
        continue;
      }

      if (!result.empty()) {
        result = prev;
        continue;
      }
    }

    result /= entry;
  }
  return result;
}

inline auto operator==(PathIterator const& lhs, PathIterator const& rhs) noexcept -> bool {
  return lhs._rest.data() == rhs._rest.data()
      && lhs._current.data() == rhs._current.data();
}

inline auto operator!=(PathIterator const& lhs, PathIterator const& rhs) noexcept -> bool {
  return lhs._rest.data() != rhs._rest.data()
      || lhs._current.data() != rhs._current.data();
}
} // namespace impl

using impl::Path;
} // namespace filesystem
} // namespace cds

#endif // CDS_FILESYSTEM_PATH_HPP
