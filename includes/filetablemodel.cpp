/* FileTableModel.cpp:

   Copyright (C) 2017-2018 Christian Schenk

   This file is part of the MiKTeX UI Library.

   The MiKTeX UI Library is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2, or
   (at your option) any later version.

   The MiKTeX UI Library is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the MiKTeX UI Library; if not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA. */

#include "filetablemodel.hpp"

#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include <QLocale>

FileTableModel::FileTableModel(QObject* parent) :
    QAbstractTableModel(parent)
{}

int FileTableModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : static_cast<int>(files.size());
}

int FileTableModel::columnCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : 2;
}

QVariant FileTableModel::data(const QModelIndex& index, int role) const
{
    if (!(index.isValid() && index.row() >= 0 && index.row() < files.size()))
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        QFileInfo file(files[index.row()]);
        switch (index.column())
        {
        case 0:
            return file.fileName();
        case 1:
            QLocale l;
            return l.formattedDataSize(file.size());
        }
    }

    return QVariant();
}

QVariant FileTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return tr("File name");
        case 1:
            return tr("Size");
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

void FileTableModel::newFiles(const QDir& dir) {
    files.clear();
    QDirIterator it(dir);
    while(it.hasNext()) {
        QFileInfo fi(it.next());
        if(fi.isFile())
            files << fi.absoluteFilePath();
    }
    emit layoutChanged();
}

void FileTableModel::clear()
{
    files.clear();
    emit layoutChanged();
}
