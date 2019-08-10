import os

#------------------------------------------------------------------------------

class FilesCollector:

	def __init__(self, source_dir, extensions):
		self._source_dir = source_dir
		self._extensions = extensions

#------------------------------------------------------------------------------

	def run(self):
		self._result = []
		self._get_files(self._source_dir)
		return self._result

#------------------------------------------------------------------------------

	def _get_files(self, dir):
		dir_content = os.listdir(dir)

		for item_name in dir_content:
			item_path = os.path.join(dir, item_name)
			self._process_item(item_path)

#------------------------------------------------------------------------------

	def _process_item(self, item_path):
		if os.path.isdir(item_path):
			self._get_files(item_path)

		elif self._is_required_file(item_path):
			relative_path = os.path.relpath(item_path, self._source_dir)
			self._result.append(relative_path)

#------------------------------------------------------------------------------

	def _is_required_file(self, file):
		return os.path.splitext(file)[1] in self._extensions

#------------------------------------------------------------------------------
