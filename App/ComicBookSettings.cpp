#include "ComicBookSettings.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QSettings>

/// Chemin à ajuster.
QString ComicBookSettings::m_cbstp_folder = "E:/documents/Code/CodeBlocks/ComicBookReader/App/Setup/" ;

ComicBookSettings::ComicBookSettings ()
{
    m_path_to_archive = "" ;
    m_path_to_cb = "" ;
    m_number_pages_displayed = 1 ;
    m_current_page = 0 ;
    m_reading_style = e_reading_style::OCCIDENTAL ;
}


ComicBookSettings::~ComicBookSettings()
{

}


enum e_code_cbstp ComicBookSettings::parseCBSTP (QString name)
{
    QString path = m_cbstp_folder + name + ".cbstp" ;

    QFile file ;
    if (!file.exists(path))
        return CBSTP_NO_EXISTS ;

    file.setFileName(path) ;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return CBSTP_OPEN_FAIL ;

    //
    //  Analyse du fichier ligne par ligne.
    //

    QTextStream stream (&file) ;

    //  Création du tableau des attributs devant être présents dans le fichier.
    QVector<QString> awaited_att ;
    awaited_att.push_back("Archive");
    awaited_att.push_back("Folder");
    awaited_att.push_back("CurrentPage");
    awaited_att.push_back("NumberPagesDisplayed");
    awaited_att.push_back("ReadingStyle");
    int current_att = 0 ;
    while (!stream.atEnd())
    {
        QString line = stream.readLine() ;
        QStringList list = line.split(':', QString::SkipEmptyParts) ;
        if (list.size() != 2)
        {
            file.close();
            return CBSTP_INVALID ;
        }

        if (list[0] != awaited_att[current_att])
        {
            file.close();
            return CBSTP_INVALID ;
        }

        //  On teste le caractère convertible des paramètres entiers.
        if (current_att == 2 or current_att == 3 or current_att == 4)
        {
            bool ok = false ;
            list[1].toInt(&ok) ;
            if (!ok)
            {
                file.close();
                return CBSTP_INVALID ;
            }
        }

        current_att++ ;
        if (current_att == awaited_att.size())
        {
            file.close();
            return CBSTP_OK ;
        }
    }

    //  Si on arrive ici c'est que le fichier est incomplet.
    file.close();
    return CBSTP_INVALID ;
}


void ComicBookSettings::saveComicBookSettings ()
{
    //  On ne sauvegarde les données que si les chemins vers l'archive et le dossier
    //  décompressé sont spécifiés.
    if (m_path_to_archive == "" or m_path_to_cb == "")
        return ;

    //  Récupération du nom du Comic Book.
    QDir comic_book_dir(m_path_to_cb) ;
    QString cb_name = comic_book_dir.dirName () ;

    //  Écriture des options.
    QString path = m_cbstp_folder + cb_name + ".cbstp" ;
    QFile file(path) ;
    file.open(QIODevice::WriteOnly | QIODevice::Text) ;

    QString line = "" ;
    //  Écriture de l'attribut "Archive".
    line = "Archive:" + m_path_to_archive + "\n" ;
    file.write(line.toStdString().c_str()) ;

    //  Écriture de l'attribut "Folder".
    line = "Folder:" + m_path_to_cb + "\n" ;
    file.write(line.toStdString().c_str()) ;

    //  Écriture de l'attribut "CurrentPage".
    line = "CurrentPage:" + QString::number(m_current_page) + "\n" ;
    file.write(line.toStdString().c_str()) ;

    //  Écriture de l'attribut "NumberPagesDisplayed".
    line = "NumberPagesDisplayed:" + QString::number(m_number_pages_displayed) + "\n" ;
    file.write(line.toStdString().c_str()) ;

    //  Écriture de l'attribut "ReadingStyle".
    line = "ReadingStyle:" + QString::number((int) m_reading_style) + "\n" ;
    file.write(line.toStdString().c_str()) ;

    file.close() ;
}


bool ComicBookSettings::loadComicBookSettings (QString comic_book_name)
{
    //
    //  Analyse du fichier.
    //
    e_code_cbstp code ;
    code = parseCBSTP(comic_book_name) ;
    switch (code)
    {
    case CBSTP_NO_EXISTS:
        return false ;
        break ;
    case CBSTP_INVALID:
        QMessageBox::information(0,"Erreur - Réouverture Comic Book",
                                 "Le fichier d'options du Comic Book " + comic_book_name + " est erroné. Suppression de ce dernier.") ;
        QFile::remove(m_cbstp_folder + comic_book_name + ".cbstp") ;
        return false ;
        break ;
    default:
        break ;
    }

    //
    //  Récupération des données du fichier.
    //
    QFile file(m_cbstp_folder + comic_book_name + ".cbstp") ;
    file.open(QIODevice::ReadOnly | QIODevice::Text) ;
    QTextStream stream (&file) ;

    QString line = "" ;
    QStringList list ;
    //  Attribut "Archive".
    line = stream.readLine() ;
    list = line.split(':', QString::SkipEmptyParts) ;
    m_path_to_archive = list[1] ;

    //  Attribut "Folder".
    line = stream.readLine() ;
    list = line.split(':', QString::SkipEmptyParts) ;
    m_path_to_cb = list[1] ;

    //  Attribut "CurrentPage".
    line = stream.readLine() ;
    list = line.split(':', QString::SkipEmptyParts) ;
    m_current_page = abs(list[1].toInt()) ;

    //  Attribut "NumberPagesDisplayed".
    line = stream.readLine() ;
    list = line.split(':', QString::SkipEmptyParts) ;
    m_number_pages_displayed = abs(list[1].toInt()) ;

    //  Attribut "ReadingStyle".
    line = stream.readLine() ;
    list = line.split(':', QString::SkipEmptyParts) ;
    m_reading_style = (e_reading_style) abs(list[1].toInt()) ;

    file.close() ;
    return true ;
}
