import os

from FilesCollector import FilesCollector
from PathUtils import *

#------------------------------------------------------------------------------

class FilesListsGenerator:

	def __init__(self):
		self._filters = list()

#------------------------------------------------------------------------------

	def add_filter(self, filter):
		self._filters.append(filter)

#------------------------------------------------------------------------------

	def generate_files_list(self, target_dir):
		self._collector = FilesCollector(self._get_required_extensions(), target_dir)
		for filter in self._filters:
			files = self._get_files_for_filter(filter)
			files = get_relative_paths(target_dir, files)
			files = change_delimiters_to_unix_style(files)

			output_file_path = os.path.join(target_dir, filter.output_file)
			self._write_to_file(filter.cmake_variable, output_file_path, files)

#------------------------------------------------------------------------------

	def _get_required_extensions(self):
		result = list()

		for filter in self._filters:
			for extension in filter.extensions:
				result.append(extension)

		return result

#------------------------------------------------------------------------------

	def _get_files_for_filter(self, filter):
		result = list()

		for extension in filter.extensions:
			result.extend(self._collector.get_files_by_extension(extension))

		return result

#------------------------------------------------------------------------------

	def _write_to_file(self, cmake_variable, output_file_path, files):
		if len(files) == 0:
			return

		output_file = open(output_file_path, "w")
		line_format = "\t{}\n"

		output_file.write("set(\n")
		output_file.write(line_format.format(cmake_variable))
		for file in files:
			output_file.write(line_format.format(file))
		output_file.write(")")

		output_file.close()

#------------------------------------------------------------------------------
