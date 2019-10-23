import os

from FilesCollector import FilesCollector
from PathUtils import *

#------------------------------------------------------------------------------

class FilesListsGenerator:

	def __init__(self):
		self._filters = list()

#------------------------------------------------------------------------------

	def add_filter(self, filter_data):
		self._filters.append(filter_data)

#------------------------------------------------------------------------------

	def generate_files_list(self, dir):
		collector = FilesCollector(self._get_required_extensions())
		collector.collect_files(dir)

		for filter in self._filters:
			files = self._get_files_for_filter(collector, filter)
			files = get_relative_paths(dir, files)
			files = change_delimiters_to_unix_style(files)

			self._write_to_file(filter.cmake_variable, filter.output_file, dir, files)

#------------------------------------------------------------------------------

	def _get_required_extensions(self):
		result = list()

		for filter in self._filters:
			for extension in filter.extensions:
				result.append(extension)

		return result

#------------------------------------------------------------------------------

	def _get_files_for_filter(self, collector, filter):
		result = list()

		for extension in filter.extensions:
			result.extend(collector.get_files_by_extension(extension))

		return result

#------------------------------------------------------------------------------

	def _write_to_file(self, cmake_variable, output_file_name, dir, files):
		if len(files) == 0:
			return

		output_file_path = os.path.join(dir, output_file_name)
		output_file = open(output_file_path, "w")

		output_file.write("set(\n")
		self._write_line(output_file, cmake_variable)
		for file in files:
			self._write_line(output_file, file)
		output_file.write(")")

		output_file.close()

#------------------------------------------------------------------------------

	def _write_line(self, file, string):
		file.write("\t{}\n".format(string))

#------------------------------------------------------------------------------
