/* FileTableModel.h:                                    -*- C++ -*-

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
#ifndef FILE_TABLE_MODEL_H
#define FILE_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QDir>

class FileTableModel : public QAbstractTableModel
{
private:
    Q_OBJECT;

public:
    FileTableModel(QObject* parent);
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void newFiles(const QDir& dir);
    void clear();

private:
    QStringList files;
};

#endif // FILE_TABLE_MODEL_H
