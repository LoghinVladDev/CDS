// DCR-TEST
// STEPS: compile(linux:gcc;linux:clang;apple:clang;apple:gcc),run(linux:gcc;linux:clang;apple:clang;apple:gcc)
// STD: 11+

#include <UnitTest.hpp>
#include <iostream>
#include <cds/filesystem/Path>
#include "../Shared.hpp"

#include <cds/Format>
#include <cds/collection/Vector>

namespace {
using cds::Vector;
using cds::String;
using cds::StringView;
using cds::filesystem::Path;
using testing::citeq;
} // namespace

#if CDS_ATTR(os_linux) || CDS_ATTR(os_apple)
TEST(PathPosixTest, nativeConv) {
  ASSERT_EQ("a/b", Path("a\\b", Path::Format::Native).str());
  ASSERT_EQ("a/b/c/d", Path("a/b\\c/d", Path::Format::Native).str());
}

TEST(PathPosixTest, portableConv) {
  ASSERT_EQ("a/b", Path("a\\b", Path::Format::Portable).str());
  ASSERT_EQ("a/b/c/d", Path("a/b\\c/d", Path::Format::Portable).str());
}

TEST(PathPosixTest, asIsConv) {
  ASSERT_EQ("a\\b", Path("a\\b", Path::Format::AsIs).str());
  ASSERT_EQ("a/b\\c/d", Path("a/b\\c/d", Path::Format::AsIs).str());
}

TEST(PathPosixTest, nativeConvIter) {
  char const p0[] = "a\\b";
  char const p1[] = "a/b\\c/d";
  ASSERT_EQ("a/b", Path(cds::begin(p0), cds::end(p0), Path::Format::Native).str());
  ASSERT_EQ("a/b/c/d", Path(cds::begin(p1), cds::end(p1), Path::Format::Native).str());
}

TEST(PathPosixTest, portableConvIter) {
  char const p0[] = "a\\b";
  char const p1[] = "a/b\\c/d";
  ASSERT_EQ("a/b", Path(cds::begin(p0), cds::end(p0), Path::Format::Portable).str());
  ASSERT_EQ("a/b/c/d", Path(cds::begin(p1), cds::end(p1), Path::Format::Portable).str());
}

TEST(PathPosixTest, asIsConvIter) {
  char const p0[] = "a\\b";
  char const p1[] = "a/b\\c/d";
  ASSERT_EQ("a\\b", Path(cds::begin(p0), cds::end(p0), Path::Format::AsIs).str());
  ASSERT_EQ("a/b\\c/d", Path(cds::begin(p1), cds::end(p1), Path::Format::AsIs).str());
}

TEST(PathPosixTest, assignOp) {
  Path p;
  ASSERT_EQ("", p.str());
  p = "a/b\\c/d";
  ASSERT_EQ("a/b/c/d", p.str());
}

TEST(PathPosixTest, assignMvNative) {
  Path p;
  ASSERT_EQ("", p.str());
  p = std::move(String("a/b\\c/d"));
  ASSERT_EQ("a/b/c/d", p.str());
}

TEST(PathPosixTest, assignNative) {
  Path p;
  ASSERT_EQ("", p.str());
  p.assign("a/b\\c/d", Path::Format::Native);
  ASSERT_EQ("a/b/c/d", p.str());
}

TEST(PathPosixTest, assignPortable) {
  Path p;
  ASSERT_EQ("", p.str());
  p.assign("a/b\\c/d", Path::Format::Portable);
  ASSERT_EQ("a/b/c/d", p.str());
}

TEST(PathPosixTest, assignAsIs) {
  Path p;
  ASSERT_EQ("", p.str());
  p.assign("a/b\\c/d", Path::Format::AsIs);
  ASSERT_EQ("a/b\\c/d", p.str());
}

TEST(PathPosixTest, assignNativeIter) {
  Path p;
  ASSERT_EQ("", p.str());
  char const p0[] = "a/b\\c/d";
  p.assign(cds::begin(p0), cds::end(p0), Path::Format::Native);
  ASSERT_EQ("a/b/c/d", p.str());
}

TEST(PathPosixTest, assignPortableIter) {
  Path p;
  ASSERT_EQ("", p.str());
  char const p0[] = "a/b\\c/d";
  p.assign(cds::begin(p0), cds::end(p0), Path::Format::Portable);
  ASSERT_EQ("a/b/c/d", p.str());
}

TEST(PathPosixTest, assignAsIsIter) {
  Path p;
  ASSERT_EQ("", p.str());
  char const p0[] = "a/b\\c/d";
  p.assign(cds::begin(p0), cds::end(p0), Path::Format::AsIs);
  ASSERT_EQ("a/b\\c/d", p.str());
}

TEST(PathPosixTest, eqAppendOfPath) {
  Path p = "a/b";
  Path const s = "c/d";
  p /= s;
  ASSERT_EQ("a/b/c/d", p.str());
}

TEST(PathPosixTest, eqAppendOfPathMv) {
  Path p = "a/b";
  p /= Path{"c/d"};
  ASSERT_EQ("a/b/c/d", p.str());
}

TEST(PathPosixTest, eqAppendOfNatStr) {
  Path p = "a/b";
  p /= String{"c/d"};
  ASSERT_EQ("a/b/c/d", p.str());
}

TEST(PathPosixTest, eqAppendOfStr) {
  Path p = "a/b";
  p /= "c/d";
  ASSERT_EQ("a/b/c/d", p.str());
}

TEST(PathPosixTest, eqConcatOfPath) {
  Path p = "a/b";
  Path const s = "c/d";
  p += s;
  ASSERT_EQ("a/bc/d", p.str());
}

TEST(PathPosixTest, eqConcatOfPathMv) {
  Path p = "a/b";
  p += Path{"c/d"};
  ASSERT_EQ("a/bc/d", p.str());
}

TEST(PathPosixTest, eqConcatOfNatStr) {
  Path p = "a/b";
  p += String{"c/d"};
  ASSERT_EQ("a/bc/d", p.str());
}

TEST(PathPosixTest, eqConcatOfStr) {
  Path p = "a/b";
  p += "c/d";
  ASSERT_EQ("a/bc/d", p.str());
}

TEST(PathPosixTest, appendDoubleSlashStr) {
  ASSERT_EQ("/a/b", (Path{"/"} / "a/b").str());
  ASSERT_EQ("/a/b", (Path{"/"} / "/a/b").str());
  ASSERT_EQ("//a/b", (Path{"//"} / "a/b").str());
  ASSERT_EQ("/a/b", (Path{"/"} / "//a/b").str());
  ASSERT_EQ("////a/b", (Path{"////"} / "////a/b").str());
}

TEST(PathPosixTest, appendDoubleSlashPath) {
  Path const p0 = "a/b";
  Path const p1 = "/a/b";
  Path const p2 = "//a/b";
  Path const p3 = "////a/b";
  ASSERT_EQ("/a/b", (Path{"/"} / p0).str());
  ASSERT_EQ("/a/b", (Path{"/"} / p1).str());
  ASSERT_EQ("//a/b", (Path{"//"} / p0).str());
  ASSERT_EQ("/a/b", (Path{"/"} / p2).str());
  ASSERT_EQ("////a/b", (Path{"////"} / p3).str());
}

TEST(PathPosixTest, appendDoubleSlashPathMv) {
  ASSERT_EQ("/a/b", (Path{"/"} / Path{"a/b"}).str());
  ASSERT_EQ("/a/b", (Path{"/"} / Path{"/a/b"}).str());
  ASSERT_EQ("//a/b", (Path{"//"} / Path{"a/b"}).str());
  ASSERT_EQ("/a/b", (Path{"/"} / Path{"//a/b"}).str());
  ASSERT_EQ("////a/b", (Path{"////"} / Path{"////a/b"}).str());
}

TEST(PathPosixTest, appendIter) {
  char const p0[] = "a/b";
  ASSERT_EQ("/d/c/a/b", (Path{"/d/c"}.append(cds::begin(p0), cds::end(p0))).str());
}

TEST(PathPosixTest, concatPortable) {
  ASSERT_EQ("/d/ca/b", (Path{"/d/c"}.concat("a\\b", Path::Format::Portable)).str());
}

TEST(PathPosixTest, concatIter) {
  char const p0[] = "a/b";
  ASSERT_EQ("/d/ca/b", (Path{"/d/c"}.concat(cds::begin(p0), cds::end(p0))).str());
}

TEST(PathPosixTest, clear) {
  Path p = "a/b";
  ASSERT_EQ("a/b", p.str());
  p.clear();
  ASSERT_EQ("", p.str());
}

TEST(PathPosixTest, removeFilename) {
  ASSERT_EQ("", Path{""}.removeFilename().str());
  ASSERT_EQ("", Path{"ab"}.removeFilename().str());
  ASSERT_EQ("", Path{"ab.txt"}.removeFilename().str());
  ASSERT_EQ("", Path{"."}.removeFilename().str());
  ASSERT_EQ("/", Path{"/"}.removeFilename().str());
  ASSERT_EQ("/", Path{"/a"}.removeFilename().str());
  ASSERT_EQ("/", Path{"/a.txt"}.removeFilename().str());
  ASSERT_EQ("/", Path{"/."}.removeFilename().str());
  ASSERT_EQ("/ab", Path{"/ab/c.txt"}.removeFilename().str());
  ASSERT_EQ("/ab", Path{"/ab/"}.removeFilename().str());
  ASSERT_EQ("/ab", Path{"/ab/."}.removeFilename().str());
}

TEST(PathPosixTest, replaceFilename) {
  ASSERT_EQ("a", Path{""}.replaceFilename("a").str());
  ASSERT_EQ("a", Path{"ab"}.replaceFilename("a").str());
  ASSERT_EQ("a", Path{"ab.txt"}.replaceFilename("a").str());
  ASSERT_EQ("a", Path{"."}.replaceFilename("a").str());
  ASSERT_EQ("/a", Path{"/"}.replaceFilename("a").str());
  ASSERT_EQ("/a", Path{"/a"}.replaceFilename("a").str());
  ASSERT_EQ("/a", Path{"/a.txt"}.replaceFilename("a").str());
  ASSERT_EQ("/a", Path{"/."}.replaceFilename("a").str());
  ASSERT_EQ("/ab/a", Path{"/ab/c.txt"}.replaceFilename("a").str());
  ASSERT_EQ("/ab/a", Path{"/ab/"}.replaceFilename("a").str());
  ASSERT_EQ("/ab/a", Path{"/ab/."}.replaceFilename("a").str());
}

TEST(PathPosixTest, replaceFilenamePortable) {
  ASSERT_EQ("a/b", Path{""}.replaceFilename("a\\b", Path::Format::Portable).str());
}

TEST(PathPosixTest, replaceFilenameIter) {
  char const p0[] = "a\\b";
  ASSERT_EQ("a/b", Path{""}.replaceFilename(cds::begin(p0), cds::end(p0), Path::Format::Portable).str());
}

TEST(PathPosixTest, replaceExtension) {
  ASSERT_EQ("/foo/bar.png", Path{"/foo/bar.jpg"}.replaceExtension(".png").str());
  ASSERT_EQ("/foo/bar.png", Path{"/foo/bar.jpg"}.replaceExtension("png").str());
  ASSERT_EQ("/foo/bar.", Path{"/foo/bar.jpg"}.replaceExtension(".").str());
  ASSERT_EQ("/foo/bar", Path{"/foo/bar.jpg"}.replaceExtension("").str());
  ASSERT_EQ("/foo/bar.png", Path{"/foo/bar."}.replaceExtension("png").str());
  ASSERT_EQ("/foo/bar.png", Path{"/foo/bar"}.replaceExtension(".png").str());
  ASSERT_EQ("/foo/bar.png", Path{"/foo/bar"}.replaceExtension("png").str());
  ASSERT_EQ("/foo/bar.", Path{"/foo/bar"}.replaceExtension(".").str());
  ASSERT_EQ("/foo/bar", Path{"/foo/bar"}.replaceExtension("").str());
  ASSERT_EQ("/foo/..png", Path{"/foo/."}.replaceExtension(".png").str());
  ASSERT_EQ("/foo/..png", Path{"/foo/."}.replaceExtension("png").str());
  ASSERT_EQ("/foo/..", Path{"/foo/."}.replaceExtension(".").str());
  ASSERT_EQ("/foo/.", Path{"/foo/."}.replaceExtension("").str());
  ASSERT_EQ("/foo/.png", Path{"/foo/"}.replaceExtension(".png").str());
  ASSERT_EQ("/foo/.png", Path{"/foo/"}.replaceExtension("png").str());
}

TEST(PathPosixTest, replaceExtensionIter) {
  char const ext[] = "png";
  ASSERT_EQ("/foo/bar.png", Path{"/foo/bar"}.replaceExtension(cds::begin(ext), cds::end(ext)).str());
}

TEST(PathPosixTest, root) {
  ASSERT_EQ("", Path{""}.root().str());
  ASSERT_EQ("", Path{"a"}.root().str());
  ASSERT_EQ("", Path{"a/b"}.root().str());
  ASSERT_EQ("/", Path{"/"}.root().str());
  ASSERT_EQ("/", Path{"/a"}.root().str());
  ASSERT_EQ("/", Path{"/a/b"}.root().str());
}

TEST(PathPosixTest, parent) {
  ASSERT_EQ("", Path{""}.parent().str());
  ASSERT_EQ("", Path{"a"}.parent().str());
  ASSERT_EQ("a", Path{"a/b"}.parent().str());
  ASSERT_EQ("/", Path{"/"}.parent().str());
  ASSERT_EQ("/", Path{"/a"}.parent().str());
  ASSERT_EQ("/a", Path{"/a/b"}.parent().str());
}

TEST(PathPosixTest, filename) {
  ASSERT_EQ("bar.txt", Path{"/foo/bar.txt"}.filename());
  ASSERT_EQ(".bar", Path{"/foo/.bar"}.filename());
  ASSERT_EQ("", Path{"/foo/bar/"}.filename());
  ASSERT_EQ(".", Path{"/foo/."}.filename());
  ASSERT_EQ("..", Path{"/foo/.."}.filename());
  ASSERT_EQ(".", Path{"."}.filename());
  ASSERT_EQ("..", Path{".."}.filename());
  ASSERT_EQ("", Path{"/"}.filename());
  ASSERT_EQ("host", Path{"//host"}.filename());
}

TEST(PathPosixTest, stemAndExtension) {
  ASSERT_EQ("bar.", Path{"/foo/bar."}.stem());
  ASSERT_EQ(".", Path{"/foo/."}.stem());
  ASSERT_EQ("bar", Path{"/foo/bar.txt"}.stem());
  ASSERT_EQ(".bar", Path{"/foo/.bar"}.stem());
  ASSERT_EQ("foo.bar.baz", Path{"foo.bar.baz.tar"}.stem());

  ASSERT_EQ("", Path{"/foo/bar."}.extension());
  ASSERT_EQ("", Path{"/foo/."}.extension());
  ASSERT_EQ(".tar", Path{"foo.bar.baz.tar"}.extension());
  ASSERT_EQ(".baz", Path{"foo.bar.baz"}.extension());
  ASSERT_EQ(".bar", Path{"foo.bar"}.extension());
}

TEST(PathPosixTest, empty) {
  ASSERT_TRUE(Path{}.empty());
  ASSERT_FALSE(Path{"/"}.empty());
  ASSERT_FALSE(Path{"/abc/def"}.empty());
}

#ifndef CDS_DISABLE_POSIX_PATH_EXISTS_TEST
TEST(PathPosixTest, exists) {
  ASSERT_TRUE(Path{"/"}.exists());
  ASSERT_TRUE(Path{"/bin"}.exists());
  ASSERT_FALSE(Path{"/i_hope_this_does_not_exist_in_your_root_if_so_why"}.exists());
}
#endif

TEST(PathPosixTest, isRelative) {
  ASSERT_TRUE(Path{"a/b"}.isRelative());
  ASSERT_TRUE(Path{"."}.isRelative());
  ASSERT_TRUE(Path{"./a/b"}.isRelative());
  ASSERT_FALSE(Path{"/"}.isRelative());
  ASSERT_FALSE(Path{"/a/b"}.isRelative());
}

TEST(PathPosixTest, isAbsolute) {
  ASSERT_FALSE(Path{"a/b"}.isAbsolute());
  ASSERT_FALSE(Path{"."}.isAbsolute());
  ASSERT_FALSE(Path{"./a/b"}.isAbsolute());
  ASSERT_TRUE(Path{"/"}.isAbsolute());
  ASSERT_TRUE(Path{"/a/b"}.isAbsolute());
}

TEST(PathPosixTest, hasRoot) {
  ASSERT_FALSE(Path{""}.hasRoot());
  ASSERT_FALSE(Path{"."}.hasRoot());
  ASSERT_FALSE(Path{"a/b"}.hasRoot());
  ASSERT_TRUE(Path{"/"}.hasRoot());
  ASSERT_TRUE(Path{"/a/b"}.hasRoot());
}

TEST(PathPosixTest, hasParent) {
  ASSERT_FALSE(Path{""}.hasParent());
  ASSERT_FALSE(Path{"."}.hasParent());
  ASSERT_TRUE(Path{"a/b"}.hasParent());
  ASSERT_FALSE(Path{"/"}.hasParent());
  ASSERT_TRUE(Path{"/a/b"}.hasParent());
  ASSERT_TRUE(Path{"/a"}.hasParent());
}

TEST(PathPosixTest, hasFilename) {
  ASSERT_TRUE(Path{"/a"}.hasFilename());
  ASSERT_TRUE(Path{"/."}.hasFilename());
  ASSERT_TRUE(Path{"a"}.hasFilename());
  ASSERT_TRUE(Path{"a/."}.hasFilename());
  ASSERT_FALSE(Path{"a/"}.hasFilename());
  ASSERT_FALSE(Path{"/"}.hasFilename());
  ASSERT_FALSE(Path{"/a/b/"}.hasFilename());
}

TEST(PathPosixTest, hasStem) {
  ASSERT_TRUE(Path{"/a"}.hasStem());
  ASSERT_TRUE(Path{"/."}.hasStem());
  ASSERT_TRUE(Path{"a"}.hasStem());
  ASSERT_TRUE(Path{"a/."}.hasStem());
  ASSERT_FALSE(Path{"a/"}.hasStem());
  ASSERT_FALSE(Path{"/"}.hasStem());
  ASSERT_FALSE(Path{"/a/b/"}.hasStem());
}

TEST(PathPosixTest, hasExtension) {
  ASSERT_TRUE(Path{"a.txt"}.hasExtension());
  ASSERT_TRUE(Path{"..txt"}.hasExtension());
  ASSERT_FALSE(Path{".txt"}.hasExtension());
  ASSERT_FALSE(Path{"/"}.hasExtension());
  ASSERT_FALSE(Path{"/.txt"}.hasExtension());
  ASSERT_TRUE(Path{"/..txt"}.hasExtension());
}

TEST(PathPosixTest, iter) {
  ASSERT_TRUE(citeq(Path{"a/b"}, std::initializer_list<char const*>{"a", "b"}));
  ASSERT_TRUE(citeq(Path{"a/b/c/d"}, std::initializer_list<char const*>{"a", "b", "c", "d"}));
  ASSERT_TRUE(citeq(Path{"/a/b"}, std::initializer_list<char const*>{"/", "a", "b"}));
  ASSERT_TRUE(citeq(Path{"/"}, std::initializer_list<char const*>{"/"}));
  ASSERT_TRUE(citeq(Path{"//"}, std::initializer_list<char const*>{"/"}));
  ASSERT_TRUE(citeq(Path{"////"}, std::initializer_list<char const*>{"/"}));
  ASSERT_TRUE(citeq(Path{"/a//b"}, std::initializer_list<char const*>{"/", "a", "b"}));
  ASSERT_TRUE(citeq(Path{"a/////b////c/d////e"}, std::initializer_list<char const*>{"a", "b", "c", "d", "e"}));
  ASSERT_TRUE(citeq(Path{"a/b/"}, std::initializer_list<char const*>{"a", "b"}));
  ASSERT_TRUE(citeq(Path{"a/b/////"}, std::initializer_list<char const*>{"a", "b"}));
}

TEST(PathPosixTest, normalizedCurrentDir) {
  ASSERT_EQ("a/b", Path{"a/./b"}.normalized().str());
  ASSERT_EQ("a", Path{"a/./"}.normalized().str());
  ASSERT_EQ("a", Path{"a/."}.normalized().str());
  ASSERT_EQ("b", Path{"./b"}.normalized().str());
  ASSERT_EQ("/b", Path{"/./b"}.normalized().str());
  ASSERT_EQ("/", Path{"/./"}.normalized().str());
  ASSERT_EQ("/", Path{"/."}.normalized().str());
  ASSERT_EQ("", Path{"./"}.normalized().str());
  ASSERT_EQ("", Path{"."}.normalized().str());
  ASSERT_EQ("", Path{"./."}.normalized().str());
  ASSERT_EQ("", Path{"././."}.normalized().str());
  ASSERT_EQ("a.", Path{"a."}.normalized().str());
  ASSERT_EQ("a.", Path{"a./."}.normalized().str());
}

TEST(PathPosixTest, normalizedPrevDir) {
  ASSERT_EQ("a/b", Path{"a/c/../b"}.normalized().str());
  ASSERT_EQ("a/b", Path{"a/b/c/.."}.normalized().str());
  ASSERT_EQ("a", Path{"a/b/c/../.."}.normalized().str());
  ASSERT_EQ("a/b", Path{"a/b/c/../c/.."}.normalized().str());
  // ASSERT_EQ("..", Path{"a/../b/../.."}.normalized().str());
  // ASSERT_EQ("../..", Path{"a/../b/../../c/../.."}.normalized().str());
  // ASSERT_EQ("../c", Path{"a/../b/../../c"}.normalized().str());
}
#endif
