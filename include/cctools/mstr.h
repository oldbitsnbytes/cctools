//
// Created by oldlonecoder on 2025-10-05.
//

//#ifndef CATUI_STRING_H
//#define CATUI_STRING_H
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
#include <cctools/geometry.h>


#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <cmath>
#include <functional>
#include <string>
#include <chrono>
#include <stack>


namespace cpp
{

using namespace integers;

class mstr final
{

    std::string _str{};
public:
    using list = std::vector<std::string>;
    using view_list = std::vector<std::string_view>;

    mstr() = default;
    mstr(const std::string& a_str);
    mstr(std::string_view a_str) { _str  = a_str; }
    mstr(const char* a_str);
    mstr(const mstr& a_str);
    mstr(char a_ch);
    mstr(integers::u8 v);
    mstr(integers::u16 v);
    mstr(integers::u32 v);
    mstr(integers::u64 v);
    mstr(integers::i8 v);
    mstr(integers::i16 v);
    mstr(integers::i32 v);
    mstr(integers::i64 v);

    mstr(float v);

    ~mstr();

    mstr& operator=(const mstr& a_str);
    mstr& operator=(const char* a_str);
    mstr& operator=(char a_ch);
    mstr& operator=(integers::u8 v);
    mstr& operator=(integers::u16 v);
    mstr& operator=(integers::u32 v);
    mstr& operator=(integers::u64 v);
    mstr& operator=(integers::i8 v);
    mstr& operator=(integers::i16 v);
    mstr& operator=(integers::i32 v);
    mstr& operator=(integers::i64 v);
    mstr& operator=(const std::string& a_str);
    mstr& operator=(float v);
    mstr& operator=(double v);

    template<typename T> mstr &operator>>(T &out)
    {
        std::istringstream in(_str); //  When string was derived from std::string ... Oops!  std::istringstream IsIn(*this);

        // if constexpr (std::is_same_v<float,T>           || std::is_same_v<double,  T> ||
        //               std::is_same_v<long double,T>     || std::is_same_v<int,     T> ||
        //               std::is_same_v<unsigned int,T>    || std::is_same_v<int8_t,  T> ||
        //               std::is_same_v<uint8_t, T>        || std::is_same_v<int16_t, T> ||
        //               std::is_same_v<uint16_t, T>       || std::is_same_v<int32_t, T> ||
        //               std::is_same_v<uint32_t, T>       || std::is_same_v<int64_t, T> ||
        //               std::is_same_v<uint64_t, T>)
        // {
        //     in >> write;
        //     return *this;
        // }
        in >> out;
        return *this;
    }

    //-------------- input/concatenation operators. -------------------------------
    mstr& operator << (color::value color);
    mstr& operator << (color::pair colors);
    mstr& operator << (const char* a_str) { _str += a_str; return *this; }
    mstr& operator << (const std::string& a_str) { _str += a_str; return *this; }
    mstr& operator << (glyph::value);
    mstr& operator << (accent_fr::value ac);
    mstr& operator << (border::Index fri);
    mstr& operator << (char c) { _str += c; return *this;}
    mstr& operator << (int  c) { _str += std::to_string(c); return *this;}
    mstr& operator << (float  c) { _str += std::to_string(c); return *this;}
    mstr& operator << (std::string_view sv) { _str += sv; return *this; }
    mstr& operator << (const mstr& tstr) { _str += tstr(); return *this; }
    //-----------------------------------------------------------------------------

    mstr& fill(size_t n, char c=0x20);
    static std::string fill(char c, size_t n);
    [[nodiscard]] auto len() const -> size_t { return _str.length(); }
    std::string operator()()const  { return _str; }
    explicit operator std::string() { return _str; }
    explicit operator std::string() const { return _str; }
    operator bool() { return _str.empty(); }
    operator bool() const { return _str.empty(); }
    std::string::iterator begin() { return _str.begin(); }
    std::string::iterator end() { return _str.end(); }
    mstr& operator *() { return *this; }

    template<typename T> mstr& operator << (T v)
    {
        std::ostringstream out;
        out << v;
        _str += out.str();
        return *this;
    }
    void clear() { _str.clear(); }

    #pragma region tokenizer

    /*!
     * @brief tokenizer struct object
     */
    template<typename str_type=std::string_view> struct  location final
    {
        rectangle rect{}; ///< smooth transition
        integers::u32 line{1};
        integers::u32 column{1};
        integers::u32 offset{0};
        using iterator = str_type::iterator;
        iterator begin{};
        iterator end{}; ///< not the typename str_type::end() but really the last valid character pointer into the segment.
        size_t   length{0};
        std::string operator *() const;
        using list = std::vector<location>;
    };

    struct  word final
    {
        std::string::iterator begin{};
        std::string::iterator last{}; ///< not the std::string::end() but really the last valid character pointer int the word.
        integers::i64         offset{-1};
        std::string           operator *();
        void                  sync(std::string& ref) { begin=last; offset = begin-ref.begin(); };
        using list = std::vector<word>;
    };


    static constexpr const char* s_default_separators = "\\%(){}[]`$#@!;,~?^&<>=+-*/:.";
    size_t words(mstr::word::list& a_list,  bool a_keep_as_word=true, const char* a_sep = cpp::mstr::s_default_separators);


private:
    bool eat(mstr::word& w);

#pragma endregion tokenizer

public:
    static std::string make_str(const char *B, const char *E) { return {B, E}; }
    static std::string make_str(const cpp::mstr::list& _list);
    static std::vector<std::string_view> make_view_list(int Count, char **s, int offset=0);

    static std::string now(const std::string &str_fmt);
    bool empty() { return _str.empty(); }

    template<typename T> static std::string to_binary(T _arg, bool padd = false, int f = 128)
    {
        uint8_t seq;
        int nbytes = sizeof(T);

        uint8_t tableau[sizeof(T)];
        memcpy(tableau, (uint8_t *) &_arg, nbytes);
        std::string stream;
        int s = 0;
        //bool Discard = false;
        for (int x = 1; x <= nbytes; x++) {
            seq = tableau[nbytes - x];
            if ((x == 1 && !padd && !seq) || (stream.empty() && !padd && !seq))
                continue;
            for (int y = 7; y >= 0; y--) { // est-ce que le bit #y est à 1 ?
                if (s >= f) {
                    stream += ' ';
                    s = 0;
                }
                ++s;
                uint8_t b = 1 << y;
                if (b & seq)
                    stream += '1';
                else
                    stream += '0';
            }
        }
        /*tableau.Clear();*/
        return stream;
    }

    static std::string bytes(std::string_view a_seq);
    static std::string bytes(std::vector<int> a_seq);
    static std::string bytes(std::vector<integers::u8> a_seq);

    template <typename T>  std::string hex(const T& num)
    {
        std::stringstream ss;
        ss << "0x" << std::hex << num;
        return ss.str();
    }
    static cpp::mstr::list make_list(int argc, char** argv, int offset=0);





};


template<typename str_type> std::string mstr::location<str_type>::operator*() const
{
    cpp::mstr str;
    str << "{ line #" << line << " column #" << column << " offset :" << offset << " length :" << length << "}";
    return str();
}

} // namespace cpp
