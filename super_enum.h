/****************************************************************************
**
** The MIT License
** SPDX short identifier: MIT
**
** Copyright 2017 Dmitry Bravikov (email: dmitry@bravikov.pro)
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
** DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#pragma once
#ifndef SUPER_ENUM_H_20171221_143544
#define SUPER_ENUM_H_20171221_143544

#include <map>
#include <cassert>

template<typename T>
class SuperEnum
{
public:
    SuperEnum();
    explicit SuperEnum(const int &value);
    virtual ~SuperEnum();

    operator int() const;

    static const SuperEnum<T> *object(const int &value);

    static int size() { return getArchive().size(); }

private:
    const int m_value;

    static int m_freeValue;

    typedef std::map<int, const SuperEnum<T> *> Container;

    static Container &getArchive()
    {
        static Container archive;
        return archive;
    }

    SuperEnum(const SuperEnum& other);
    SuperEnum& operator=(const SuperEnum& other);
};

template<typename T>
int SuperEnum<T>::m_freeValue = 0;

template<typename T>
SuperEnum<T>::SuperEnum():
    m_value(m_freeValue++)
{
    getArchive()[m_value] = this;
}

template<typename T>
SuperEnum<T>::SuperEnum(const int &value):
    m_value(value)
{
    assert(getArchive().find(m_value) == getArchive().end());

    if (getArchive().empty()) {
        m_freeValue = m_value + 1;
    }
    else {
        if (m_freeValue <= m_value) {
            m_freeValue = m_value + 1;
        }
    }

    getArchive()[m_value] = this;
}

template<typename T>
SuperEnum<T>::~SuperEnum()
{
    getArchive().erase(m_value);
}

template<typename T>
const SuperEnum<T> *SuperEnum<T>::object(const int &value)
{
    typename Container::iterator iterator = getArchive().find(value);

    if (iterator == getArchive().end()) {
        return 0;
    }

    return iterator->second;
}

template<typename T>
SuperEnum<T>::operator int() const
{
    return m_value;
}

#endif /* #ifndef SUPER_ENUM_H_20171221_143544 */
