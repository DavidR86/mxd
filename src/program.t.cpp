// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      program.t.cpp
/// @brief     Unit tests for program.hpp.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      November 27, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "program.hpp"

// C++ Standard Library
#include <vector>

// mxd Library
#include "mxd.hpp"
#include "shader.hpp"
#include "window.hpp"

// Google Test Framework
#include <gtest/gtest.h>

TEST(Program, ParameterAccessAndCompilation) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  std::string vSource =
      "#version 330\n"
      "layout (location = 0) in vec3 aPos;\n"
      "out vec4 vertexColor;\n"
      "void main() {\n"
      "gl_Position = vec4(aPos, 1.0);\n"
      "vertexColor = vec4(0.5,0.0,0.0,1.0);\n}";

  std::string fSource =
      "#version 330\n"
      "out vec4 FragColor;\n"
      ""
      "in vec4 vertexColor;\n"
      ""
      "void main(){\n"
      "FragColor = vertexColor;}";

  std::vector<nzl::Shader> shaders;

  nzl::Shader shader1(nzl::Shader::Stage::Vertex, vSource);
  shaders.push_back(shader1);
  shaders.back().compile();
  nzl::Shader shader2(nzl::Shader::Stage::Fragment, fSource);
  shaders.push_back(shader2);
  shaders.back().compile();

  ASSERT_NO_THROW(nzl::Program program(shaders); program.compile(););

  nzl::Program program(shaders);
  EXPECT_NE(program.id(), 0u);

  nzl::terminate();
}

TEST(Program, CopyConstructor) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  std::vector<nzl::Shader> shaders;

  nzl::Program program1(shaders);
  nzl::Program program2 = program1;
  EXPECT_EQ(program1.id(), program2.id());

  nzl::terminate();
}

TEST(Program, CopyOperator) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  std::vector<nzl::Shader> shaders;

  nzl::Program program1(shaders);

  nzl::Program program3(shaders);
  EXPECT_NE(program1.id(), program3.id());
  program3 = program1;
  EXPECT_EQ(program3.id(), program1.id());

  nzl::terminate();
}

TEST(Program, Failing) {
  ASSERT_TRUE(false) << "You must add unit tests for program.hpp";
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
