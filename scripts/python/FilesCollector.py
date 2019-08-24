import os

#------------------------------------------------------------------------------

class FilesCollector:

	def __init__(self, extensions):
		self._files = dict()
		for extension in extensions:
			self._files[extension] = list()

#------------------------------------------------------------------------------

	def get_files_by_extension(self, extension):
		return self._files.get(extension)

#------------------------------------------------------------------------------

	def collect_files(self, dir):
		dir_content = os.listdir(dir)
		for item_name in dir_content:
			item_path = os.path.join(dir, item_name)

			if os.path.isdir(item_path):
				self.collect_files(item_path)
			else:
				self._process_file(item_path)

#------------------------------------------------------------------------------

	def _process_file(self, file):
		file_extenstion = os.path.splitext(file)[1]

		if file_extenstion in self._files.keys():
			self._files[file_extenstion].append(file)

#------------------------------------------------------------------------------
