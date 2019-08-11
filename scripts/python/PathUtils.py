import os

#------------------------------------------------------------------------------

def get_relative_paths(source_dir, items_list):
	return [os.path.relpath(item_path, source_dir) for item_path in items_list]

#------------------------------------------------------------------------------

def change_delimiters_to_unix_style(items_list):
	return [item_path.replace('\\', '/') for item_path in items_list]

#------------------------------------------------------------------------------
