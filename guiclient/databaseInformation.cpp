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
 * The Original Code is PostBooks Accounting, ERP, and CRM Suite. 
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
 * Powered by PostBooks, an open source solution from xTuple
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

#include "databaseInformation.h"

#include <qvariant.h>
#include <dbtools.h>

/*
 *  Constructs a databaseInformation as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
databaseInformation::databaseInformation(QWidget* parent, const char* name, bool modal, Qt::WFlags fl)
    : XDialog(parent, name, modal, fl)
{
    setupUi(this);


    // signals and slots connections
    connect(_save, SIGNAL(clicked()), this, SLOT(sSave()));
    connect(_close, SIGNAL(clicked()), this, SLOT(reject()));
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
databaseInformation::~databaseInformation()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void databaseInformation::languageChange()
{
    retranslateUi(this);
}


void databaseInformation::init()
{
  QString server;
  QString database;
  QString port;

  _description->setFocus();

  _description->setText(_metrics->value("DatabaseName"));
  _comments->setText(_metrics->value("DatabaseComments"));
  _version->setText(_metrics->value("OpenMFGServerVersion"));

  //Disable batch manager if PostBooks
  if ( (_metrics->value("Application") != "OpenMFG")
    && (_metrics->value("Application") != "xTupleERP") )
  {
    _enableBatchManager->setChecked(FALSE);
    _enableBatchManager->hide();
    _defaultFromAddress->setText("");
    _defaultFromAddress->hide();
    _defaultFromAddressLit->hide();
  }
  else
  {
    _defaultFromAddress->setText(_metrics->value("DefaultBatchFromEmailAddress"));
    _enableBatchManager->setChecked(_metrics->boolean("EnableBatchManager"));
  }

  QString protocol;
  parseDatabaseURL(omfgThis->databaseURL(), protocol, server, database, port);
  _application->setText(_metrics->value("Application"));
  _server->setText(server);
  _name->setText(database);
  
  q.exec( "SELECT numOfDatabaseUsers() AS databaseusers,"
          "       numOfServerUsers() AS serverusers;" );
  if (q.first())
  {
    _numOfDatabaseUsers->setText(q.value("databaseusers").toString());
    _numOfServerUsers->setText(q.value("serverusers").toString());
  }
//  ToDo

  if (!_privleges->check("ConfigDatabaseInfo"))
  {
    _description->setEnabled(FALSE);
    _defaultFromAddress->setEnabled(FALSE);
    _comments->setEnabled(FALSE);
    _close->setText(tr("&Close"));
    _save->hide();
  }
}

void databaseInformation::sSave()
{
  _metrics->set("DatabaseName", _description->text().stripWhiteSpace());
  _metrics->set("DefaultBatchFromEmailAddress", _defaultFromAddress->text().stripWhiteSpace());
  _metrics->set("DatabaseComments", _comments->text().stripWhiteSpace());

  _metrics->set("EnableBatchManager", _enableBatchManager->isChecked());

  _metrics->load();

  omfgThis->setCaption();

  accept();
}
