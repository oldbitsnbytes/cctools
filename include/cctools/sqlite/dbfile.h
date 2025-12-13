////////////////////////////////////////////////////////////////////////////////////////////
//   Copyright (C) ...,2025,... by Serge Lussier
//   serge.lussier@oldbitsnbytes.club / lussier.serge@gmail.com
//   ----------------------------------------------------------------------------------
//   Unless otherwise specified, all Codes and files in this project is written
//   by the author and owned by the author (Serge Lussier), unless otherwise specified.
//   ----------------------------------------------------------------------------------
//   Copyrights from authors other than Serge Lussier also apply here.
//   Open source FREE licences also apply to the code from the author (Serge Lussier)
//   ----------------------------------------------------------------------------------
//   Usual GNU FREE GPL-1,2, MIT... or whatever -  apply to this project.
//   ----------------------------------------------------------------------------------
//   NOTE : All source code that I am the only author, I reserve for myself, the rights to
//   make it to restricted private license.
////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------


#pragma once

#include <cctools/rem.h>
#include <sqlite3.h>

namespace cpp::sql
{

class dbfile
{
    rem::type   m_state{rem::type::none};
    sqlite3*    mp_db{nullptr};
    std::string m_filename{};
    char*       mp_errmsg{nullptr};
public:

    dbfile(const std::string& filename);
    ~dbfile();
    sqlite3* db_handle() { return mp_db; }
    rem::type state() const { return m_state; }
    const char* errmsg() const { return mp_errmsg; }
    bool open();
};
} // namsppace cpp::sql
