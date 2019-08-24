import os
import sys
import platform

sys.path.insert(1, "scripts/python")

from scripts.python.FilesListsGenerator import FilesListsGenerator
from scripts.python.FilterData import FilterData

#------------------------------------------------------------------------------

def create_generator(dir):
	return FilesListsGenerator(os.path.normpath(dir))

generators = []
generators.append(create_generator("src/utils"))
generators.append(create_generator("src/core"))
generators.append(create_generator("src/application"))

source_filter = FilterData("sources", "InitSources.cmake", [".hpp",".cpp"])
resource_filter = FilterData("resources", "InitResources.cmake", [".qrc"])
ui_source_filter = FilterData("ui_sources", "InitUiSources.cmake", [".qml"])

for generator in generators:
	generator.add_filter(source_filter)
	generator.add_filter(resource_filter)
	generator.add_filter(ui_source_filter)
	generator.generate_files_list()

#------------------------------------------------------------------------------
