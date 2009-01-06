  /*
 * Common Public Attribution License Version 1.0. 
 * 
 * The contents of this file are subject to the Common Public Attribution 
 * License Version 1.0 (the "License"); you may not use this file except 
 * in compliance with the License. You may obtain a copy of the License 
 * at http://www.xTuple.com/CPAL.  The License is based on the Mozilla 
 * Public License Version 1.1 but Sections 14 and 15 have been added to 
 * cover use of software over a computer network and provide for limited 
 * attribution for the Original Developer. In addition, Exhibit A has 
 * been modified to be consistent with Exhibit B.
 * 
 * Software distributed under the License is distributed on an "AS IS" 
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See 
 * the License for the specific language governing rights and limitations 
 * under the License. 
 * 
 * The Original Code is xTuple ERP: PostBooks Edition 
 * 
 * The Original Developer is not the Initial Developer and is __________. 
 * If left blank, the Original Developer is the Initial Developer. 
 * The Initial Developer of the Original Code is OpenMFG, LLC, 
 * d/b/a xTuple. All portions of the code written by xTuple are Copyright 
 * (c) 1999-2008 OpenMFG, LLC, d/b/a xTuple. All Rights Reserved. 
 * 
 * Contributor(s): ______________________.
 * 
 * Alternatively, the contents of this file may be used under the terms 
 * of the xTuple End-User License Agreeement (the xTuple License), in which 
 * case the provisions of the xTuple License are applicable instead of 
 * those above.  If you wish to allow use of your version of this file only 
 * under the terms of the xTuple License and not to allow others to use 
 * your version of this file under the CPAL, indicate your decision by 
 * deleting the provisions above and replace them with the notice and other 
 * provisions required by the xTuple License. If you do not delete the 
 * provisions above, a recipient may use your version of this file under 
 * either the CPAL or the xTuple License.
 * 
 * EXHIBIT B.  Attribution Information
 * 
 * Attribution Copyright Notice: 
 * Copyright (c) 1999-2008 by OpenMFG, LLC, d/b/a xTuple
 * 
 * Attribution Phrase: 
 * Powered by xTuple ERP: PostBooks Edition
 * 
 * Attribution URL: www.xtuple.org 
 * (to be included in the "Community" menu of the application if possible)
 * 
 * Graphic Image as provided in the Covered Code, if any. 
 * (online at www.xtuple.com/poweredby)
 * 
 * Display of Attribution Information is required in Larger Works which 
 * are defined in the CPAL as a work which combines Covered Code or 
 * portions thereof with code not governed by the terms of the CPAL.
 */

#ifndef XTREEVIEW_H

#define XTREEVIEW_H

#include <QTreeView>
#include <QMenu>

#include "xdatawidgetmapper.h"
#include "xsqltablemodel.h"
#include "OpenMFGWidgets.h"

class OPENMFGWIDGETS_EXPORT XTreeView : public QTreeView
{
    Q_OBJECT
    Q_PROPERTY(QString         schemaName            READ schemaName           WRITE setSchemaName       )
    Q_PROPERTY(QString         tableName             READ tableName            WRITE setTableName        )
    Q_PROPERTY(int             primaryKeyCoulmns     READ primaryKeyColumns    WRITE setPrimaryKeyColumns)
    Q_PROPERTY(int             size                  READ size                                             DESIGNABLE false)
    
    public:
      XTreeView(QWidget *parent = 0);

      bool         throwScriptException(const QString &message);
      int          primaryKeyColumns()       const            { return _keyColumns;         };
      QString      schemaName()              const            { return _schemaName;         };
      QString      tableName()               const            { return _tableName;          };
      void         setTable();
      
    public slots:
      virtual int  size();
      virtual QVariant value(int row, int column);
      virtual QVariant selectedValue(int column);
      virtual void insert();
      virtual void populate(int p);
      virtual void removeRows(int row, int count);
      virtual void removeSelected();
      virtual void revertAll();
      virtual void save();
      virtual void select();
      virtual void selectRow(int index);
      virtual void setDataWidgetMap(XDataWidgetMapper* mapper);
      virtual void setModel(XSqlTableModel* model=0);
      virtual void setPrimaryKeyColumns(int p)                { _keyColumns = p;            };
      virtual void setSchemaName(QString p)                   { _schemaName = p;            };
      virtual void setTableName(QString p)                    { _tableName = p;             };

    signals:
      void  newModel(XSqlTableModel *model);
      void  rowSelected(int);
      void  valid(bool);
      void  saved();
      
    protected:
      virtual void selectionChanged(const QItemSelection & selected, const QItemSelection & deselected);
      
    private:
      int               _keyColumns;
      QString           _schemaName;
      QString           _tableName;
      QSqlDatabase      *_db;
      QSqlRecord        _idx;
      XDataWidgetMapper *_mapper;
      XSqlTableModel    _model;
      QItemSelectionModel *_selectModel;
 
};

#endif
