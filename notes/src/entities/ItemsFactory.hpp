#ifndef __ITEMS_FACTORY_HPP__
#define __ITEMS_FACTORY_HPP__

//-----------------------------------------------------------------------------

class Note;
class NotesFolder;

//-----------------------------------------------------------------------------

class ItemsFactory : boost::noncopyable
{
public:
	std::unique_ptr<Note> createNote(std::string_view _text);
	std::unique_ptr<NotesFolder> createNotesFolder(std::string_view _name);
};

//-----------------------------------------------------------------------------

#endif // __ITEMS_FACTORY_HPP__
