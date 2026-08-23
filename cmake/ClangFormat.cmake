# Copyright (C) 2017-2026 Soroush Rabiei <soroush.rabiei@gmail.com>
#
# This file is part of libcalendars.
#
# libcalendars is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libcalendars is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with libcalendars.  If not, see <https://www.gnu.org/licenses/>.
#
# SPDX-License-Identifier: GPL-3.0-or-later

# Source formatting, driven by the GNU style in .clang-format at the top of the
# tree. Provides two targets:
#
#     cmake --build . --target format         rewrite every source in place
#     cmake --build . --target format-check   fail if anything is unformatted
#
# and, unless LIBCALENDARS_GIT_HOOKS is turned off, points the repository at the
# .githooks directory so that commits are formatted automatically.

find_program(CLANG_FORMAT_EXECUTABLE
    NAMES clang-format
    DOC "Path to the clang-format executable"
)

file(GLOB_RECURSE LIBCALENDARS_FORMAT_SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/lib/src/*.c"
    "${PROJECT_SOURCE_DIR}/lib/src/*.h"
    "${PROJECT_SOURCE_DIR}/lib/include/*.h"
    "${PROJECT_SOURCE_DIR}/tests/*.c"
    "${PROJECT_SOURCE_DIR}/tests/*.h"
)

if(CLANG_FORMAT_EXECUTABLE)
    add_custom_target(format
        COMMAND "${CLANG_FORMAT_EXECUTABLE}" -i --style=file
                ${LIBCALENDARS_FORMAT_SOURCES}
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        COMMENT "Formatting sources with clang-format"
        VERBATIM
    )

    add_custom_target(format-check
        COMMAND "${CLANG_FORMAT_EXECUTABLE}" --dry-run -Werror --style=file
                ${LIBCALENDARS_FORMAT_SOURCES}
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        COMMENT "Checking source formatting with clang-format"
        VERBATIM
    )
else()
    message(STATUS
        "clang-format not found; the format and format-check targets are "
        "unavailable"
    )
endif()

option(LIBCALENDARS_GIT_HOOKS "Enable the repository's git hooks" ON)

if(LIBCALENDARS_GIT_HOOKS AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # A plain worktree has .git as a directory and a linked worktree has it as a
    # file, so EXISTS covers both. The path is relative to the top of the
    # working tree, which is what git resolves core.hooksPath against.
    execute_process(
        COMMAND git config core.hooksPath .githooks
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        RESULT_VARIABLE LIBCALENDARS_HOOKS_RESULT
        OUTPUT_QUIET
        ERROR_QUIET
    )
    if(LIBCALENDARS_HOOKS_RESULT EQUAL 0)
        message(STATUS "Git hooks enabled from .githooks")
    else()
        message(STATUS "Could not enable the git hooks in .githooks")
    endif()

    # Keep the bulk reformatting revisions out of git blame.
    execute_process(
        COMMAND git config blame.ignoreRevsFile .git-blame-ignore-revs
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_QUIET
        ERROR_QUIET
    )
endif()
