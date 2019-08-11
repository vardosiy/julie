import os
import sys
import platform

sys.path.insert(1, "scripts/python")

from scripts.python.FilesListsGenerator import FilesListsGenerator

#------------------------------------------------------------------------------

targets_dirs = []
targets_dirs.append(os.path.normpath("src/utils"))
targets_dirs.append(os.path.normpath("src/core"))
targets_dirs.append(os.path.normpath("src/application"))

generator = FilesListsGenerator(targets_dirs)
generator.generate_files_lists("sources", "InitSources.cmake", [".hpp",".cpp"])
generator.generate_files_lists("resources", "InitResources.cmake", [".qrc"])
generator.generate_files_lists("ui_sources", "InitUiSources.cmake", [".qml"])

#------------------------------------------------------------------------------
