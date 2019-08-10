import os
import sys

sys.path.insert(1, "scripts/python")

from scripts import GenerateHelpers

current_dir = os.path.abspath(os.path.curdir)

project_names = []
project_names.append("src/utils")
project_names.append("src/core")
project_names.append("src/application")

GenerateHelpers.generate_sources(current_dir, project_names)