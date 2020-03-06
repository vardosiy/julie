import os

from FilesCollector import FilesCollector
from PathUtils import *

#------------------------------------------------------------------------------

class FilesListsGenerator:

	def __init__(self, filters):
		self.__filters = filters

#------------------------------------------------------------------------------

	def generate_files_lists(self, target_dir, output_file_name):
		self.__collector = FilesCollector(self.__get_required_extensions(), target_dir)

		output_file_path = os.path.join(target_dir, output_file_name)
		with open(output_file_path, "w") as output_file:
			for filter in self.__filters:
				files = self.__get_files_for_filter(filter)
				files = get_relative_paths(target_dir, files)
				files = change_delimiters_to_unix_style(files)

				if len(files) > 0:
					variable_definition = self.__create_variable_definition(filter.cmake_variable, files)
					output_file.write(variable_definition)

#------------------------------------------------------------------------------

	def __get_required_extensions(self):
		result = list()
		for filter in self.__filters:
			result.extend(filter.extensions)
		return result

#------------------------------------------------------------------------------

	def __get_files_for_filter(self, filter):
		result = list()
		for extension in filter.extensions:
			result.extend(self.__collector.get_files_by_extension(extension))
		return result

#------------------------------------------------------------------------------

	def __create_variable_definition(self, cmake_variable, files):
		line_format = "\t{}\n"

		result = "set(\n"
		result += line_format.format(cmake_variable)
		for file in files:
			result += line_format.format(file)
		result += ")\n"

		return result

#------------------------------------------------------------------------------
