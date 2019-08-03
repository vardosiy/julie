#include "Pch.hpp"

#include "core/Model.hpp"

#include "core/nodes/Note.hpp"
#include "core/nodes/NotesFolder.hpp"

#include "core/visitors/save_restore/StreamSaveVisitor.hpp"
#include "core/visitors/save_restore/StreamRestoreVisitor.hpp"

#include <fstream>

//-----------------------------------------------------------------------------

Model::Model() noexcept
{
	LOG("Creating Model");
}

//-----------------------------------------------------------------------------

Model::~Model() noexcept
{
	LOG("Destroying Model");
}

//-----------------------------------------------------------------------------

void Model::save() const
{
	LOG("Saving Model to: %1%", k_saveFile.data());

	std::ofstream fileStream(k_saveFile.data());
	writeHeader(fileStream);
	saveData(fileStream);
}

//-----------------------------------------------------------------------------

void Model::load()
{
	LOG("Saving Model from: %1%", k_saveFile.data());

	std::ifstream fileStream(k_saveFile.data());
	readHeader(fileStream);
	restoreData(fileStream);
}

//-----------------------------------------------------------------------------

void Model::writeHeader(std::ofstream & _stream) const
{
	utils::save_restore::StreamWriter writer(_stream);
}

//-----------------------------------------------------------------------------

void Model::readHeader(std::ifstream & _stream)
{
	utils::save_restore::StreamReader reader(_stream);
}

//-----------------------------------------------------------------------------

void Model::saveData(std::ofstream & _stream) const
{
	visitors::save_restore::StreamSaveVisitor visitor(_stream);
	m_notesRoot->accept(visitor);
}

//-----------------------------------------------------------------------------

void Model::restoreData(std::ifstream & _stream)
{
	m_notesRoot = std::make_unique<nodes::NotesFolder>();

	visitors::save_restore::StreamRestoreVisitor visitor(_stream);
	m_notesRoot->accept(visitor);
}

//-----------------------------------------------------------------------------
