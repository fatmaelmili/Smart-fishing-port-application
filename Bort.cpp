#include "Bort.h"
#include "ui_Bort.h"
#include<QStyle>
#include <QFileDialog>
#include <QFileInfo>
#include "stock.h"
#include <QMessageBox>
#include "connection.h"
#include <QHeaderView>
SignIn::SignIn(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignIn)
{
    ui->setupUi(this);

    // 🔥 DATABASE CONNECTION (IMPORTANT)
    connection &c = connection::createInsatance();
    if(!c.createconnect())
    {
        qDebug() << "DB connection failed";
    }
    else
    {
        qDebug() << "DB connected";
    }

    Stock s;
    QSqlQueryModel* model = s.afficher();

    ui->table_stock->setModel(model);

    // 🔥 FORCE DISPLAY FIXES
    ui->table_stock->resizeColumnsToContents();
    ui->table_stock->horizontalHeader()->setStretchLastSection(true);
    ui->table_stock->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_stock->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_stock->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_stock->show();

    // 🔥 YOUR STYLE CODE
    ui->staffmanagementBTN->setProperty("active", true);
    ui->staffmanagementBTN->style()->unpolish(ui->staffmanagementBTN);
    ui->staffmanagementBTN->style()->polish(ui->staffmanagementBTN);
    ui->staffmanagementBTN->update();
    ui->table_stock->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_stock->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->fishingzonemanagementBTNZ->setProperty("active", true);
    ui->fishingzonemanagementBTNZ->style()->unpolish(ui->fishingzonemanagementBTNZ);
    ui->fishingzonemanagementBTNZ->style()->polish(ui->fishingzonemanagementBTNZ);
    ui->fishingzonemanagementBTNZ->update();
    refreshStockTable();
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_addspecies_stock_clicked()
{
    qDebug() << "BUTTON CLICKED";

    int qte = ui->quantity_stock->text().toInt();
    QString type = ui->speciesname_stock->text();
    QString etat = ui->status_stock->currentText();

    qDebug() << qte << type << etat; // 🔥 debug values

    Stock s(qte, type, etat);

    if(s.ajouter())
    {
        QMessageBox::information(this, "Success", "Stock added!");
        ui->table_stock->setModel(s.afficher());
    }
    else
    {
        QMessageBox::critical(this, "Error", "Insert failed!");
    }
}

void SignIn::on_update_stock_clicked()
{
    qDebug() << "EDIT BUTTON CLICKED";
    int row = ui->table_stock->selectionModel()->currentIndex().row();

    if(row == -1)
    {
        QMessageBox::warning(this, "Error", "Select a row!");
        return;
    }

    int id = ui->table_stock->model()->index(row, 0).data().toInt();

    int qte = ui->quantity_stock->text().toInt();
    QString type = ui->speciesname_stock->text();
    QString etat = ui->status_stock->currentText();

    Stock s(qte, type, etat);

    if(s.modifier(id))
    {
        QMessageBox::information(this, "Success", "Updated!");
        ui->table_stock->setModel(s.afficher());
    }
    else
    {
        QMessageBox::critical(this, "Error", "Update failed!");
    }
     qDebug() << "EDIT BUTTON CLICKED";
}

void SignIn::on_delete_stock_clicked()
{
    int row = ui->table_stock->currentIndex().row();

    if(row == -1)
    {
        QMessageBox::warning(this, "Error", "Select a row!");
        return;
    }

    int id = ui->table_stock->model()->index(row, 0).data().toInt();

    Stock s;

    if(s.supprimer(id))
    {
        QMessageBox::information(this, "Success", "Deleted!");
        ui->table_stock->setModel(s.afficher());
    }
    else
    {
        QMessageBox::critical(this, "Error", "Delete failed!");
    }
}

void SignIn::refreshStockTable()
{
    Stock s;
    QSqlQueryModel* model = s.afficher();
    ui->table_stock->setModel(nullptr);
    ui->table_stock->setModel(model);
}

void SignIn::on_btnForgetmdp_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageForgetpass);
}


void SignIn::on_backsigninBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_resetbtn_clicked()
{

        QString input = ui->resetlineEdit->text().trimmed();

        if (input.isEmpty()) {
            ui->resetlabel->setText("Please enter your email or username.");
            return;
        }

        ui->resetlabel->setText("Reset link sent. Check your email.");


}


void SignIn::on_ubploacvbtn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select a CV",
        QDir::homePath(),
        "CV (*.pdf *.doc *.docx);;Tous les fichiers (*.*)"
        );

    if (filePath.isEmpty())
        return;

    // Afficher le chemin du fichier dans le champ
    //ui->cvpathEdit->setText(filePath);
    ui->cvpathEdit->setText(QFileInfo(filePath).fileName());

}


void SignIn::on_signinbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}


void SignIn::on_staffmanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}




void SignIn::on_backstfbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_backWbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}


void SignIn::on_staticbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->staffdash);
}


void SignIn::on_backWbtn_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);

}


void SignIn::on_staticbtn_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->staffdash);
}


void SignIn::on_modifystaffbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdate);

}


void SignIn::on_logOutBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_logOutBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_backWbtn_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}


void SignIn::on_userprofiledetails_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_userprofiledetails_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_userprofiledetails_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_userprofiledetails_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}




void SignIn::on_userprofiledetails_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_staffmanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_logOutBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_userprofiledetails_Z_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_fishingzonemanagementBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_fishingzonemanagementBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_fishingzonemanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_fishingzonemanagementBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_fishingzonemanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}



void SignIn::on_fishingzonemanagementBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_stockmanagementBTN_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_userprofiledetails_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_fishingzonemanagementBTN_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_logOutBTN_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_stockmanagementBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);

    // 🔥 LOAD DATA WHEN PAGE OPENS
    Stock s;
    ui->table_stock->setModel(s.afficher());
}


void SignIn::on_staffmanagementBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}

void SignIn::on_table_stock_clicked(const QModelIndex &index)
{
    int row = index.row();

    ui->quantity_stock->setText(
        ui->table_stock->model()->index(row, 1).data().toString()
        );

    ui->speciesname_stock->setText(
        ui->table_stock->model()->index(row, 2).data().toString()
        );

    ui->status_stock->setCurrentText(
        ui->table_stock->model()->index(row, 3).data().toString()
        );
}

void SignIn::on_stockmanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
    Stock s;
    ui->table_stock->setModel(s.afficher());
}


void SignIn::on_stockmanagementBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
    Stock s;
    ui->table_stock->setModel(s.afficher());
}


void SignIn::on_stockmanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
    Stock s;
    ui->table_stock->setModel(s.afficher());
}


void SignIn::on_stockmanagementBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
    Stock s;
    ui->table_stock->setModel(s.afficher());
}


void SignIn::on_stockmanagementBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
    Stock s;
    ui->table_stock->setModel(s.afficher());
}


void SignIn::on_logOutBTNe_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_fishingzonemanagementBTNe_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_stockmanagementBTNe_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
    refreshStockTable();
}


void SignIn::on_staffmanagementBTNe_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_userprofiledetailsE_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_backWbtnE_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}


void SignIn::on_equipmentmanagementBTN_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_equipmentmanagementBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_staffmanagementBTNA_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_stockmanagementBTNA_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
    refreshStockTable();
}


void SignIn::on_equipmentmanagementBTNA_clicked()
{
  ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_fishingzonemanagementBTNA_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_logOutBTNA_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_userprofileC_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_mainpagebtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}


void SignIn::on_clientdashboardbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->dashC);
}


void SignIn::on_staffmanagementBTN_DC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageStaffManagement);
}


void SignIn::on_stockmanagementBTN_D_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishStock);
    refreshStockTable();
}


void SignIn::on_equipmentmanagementBTN_DC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageEquipment);
}


void SignIn::on_fishingzonemanagementBTN_DC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFishingZone);
}


void SignIn::on_logOutBTN_DC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSignIn);
}


void SignIn::on_userprofiledetails_DC_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageupdateaccount);
}


void SignIn::on_backtoclientbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTNe_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_stock_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTNZ_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_W_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_U_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_A_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}


void SignIn::on_clientsmanagementBTN_D_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageClients);
}

