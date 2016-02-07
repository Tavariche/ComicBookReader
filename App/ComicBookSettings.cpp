#include "ComicBookSettings.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QSettings>


ComicBookSettings::ComicBookSettings ()
{
    /// Chemin à ajuster.
    m_cbstp_folder = "E:/documents/Code/CodeBlocks/ComicBookReader/App/Setup/" ;

    m_path_to_archive = "" ;
    m_number_pages_displayed = 1 ;
    m_current_page = 0 ;
    m_reading_style = e_reading_style::OCCIDENTAL ;
}


ComicBookSettings::~ComicBookSettings()
{

}


e_loading_status ComicBookSettings::loadSettings (QString name)
{
    //  Test de l'existence du fichier .cbstp associé.
    QString path = m_cbstp_folder + name + ".cbstp" ;
    QFile file ;
    file.setFileName(path) ;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return CBSTP_INVALID ;

    //
    //  Analyse du fichier ligne par ligne.
    //
    QTextStream stream (&file) ;

    //  Attribut "Archive".
    QString line = stream.readLine() ;
    if (line.section(':',0,0) != "Archive")
    {
        file.close();
        QFile::remove(path) ;
        return CBSTP_INVALID ;
    }
    //  Test de l'existence de l'archive à l'endroit spécifié.
    if(!QFile::exists(line.section(':',1)))
    {
        file.close();
        QFile::remove(path) ;
        return CBSTP_INVALID ;
    }
    m_path_to_archive = line.section(':',1) ;



    //  Attribut "ReadingStyle".
    line = stream.readLine() ;
    QStringList list = line.split(':', QString::SkipEmptyParts) ;
    if (list.size() != 2)
    {
        file.close();
        QFile::remove(path) ;
        return CBSTP_ARCHIVE_OK ;
    }
    else if (list[0] != "ReadingStyle")
    {
        file.close();
        QFile::remove(path) ;
        return CBSTP_ARCHIVE_OK ;
    }
    //  Test de la convertibilité en entier du paramètre.
    bool ok = false ;
    list[1].toInt(&ok) ;
    if (!ok)
    {
        file.close();
        QFile::remove(path) ;
        return CBSTP_ARCHIVE_OK ;
    }
    m_reading_style = (e_reading_style) abs(list[1].toInt()) ;
    //  Vérification de la validité de la valeur récupérée.
    if (m_reading_style != ORIENTAL and m_reading_style != OCCIDENTAL)
        m_reading_style = OCCIDENTAL ;



    //  Attribut "NumberPagesDisplayed".
    line = stream.readLine() ;
    list = line.split(':', QString::SkipEmptyParts) ;
    if (list.size() != 2)
    {
        file.close();
        QFile::remove(path) ;
        return CBSTP_ARCHIVE_OK ;
    }
    else if (list[0] != "NumberPagesDisplayed")
    {
        file.close();
        QFile::remove(path) ;
        return CBSTP_ARCHIVE_OK ;
    }
    //  Test de la convertibilité en entier du paramètre.
    ok = false ;
    list[1].toInt(&ok) ;
    if (!ok)
    {
        file.close();
        QFile::remove(path) ;
        return CBSTP_ARCHIVE_OK ;
    }
    m_number_pages_displayed = abs(list[1].toInt()) ;
    //  Vérification de la validité de la valeur récupérée.
    if (m_number_pages_displayed > 2 or m_number_pages_displayed == 0)
        m_number_pages_displayed = 1 ;



    //  Attribut "CurrentPage".
    line = stream.readLine() ;
    list = line.split(':', QString::SkipEmptyParts) ;
    if (list.size() != 2)
    {
        file.close();
        QFile::remove(path) ;
        return CBSTP_ARCHIVE_OK ;
    }
    else if (list[0] != "CurrentPage")
    {
        file.close();
        QFile::remove(path) ;
        return CBSTP_ARCHIVE_OK ;
    }
    //  Test de la convertibilité en entier du paramètre.
    ok = false ;
    list[1].toInt(&ok) ;
    if (!ok)
    {
        file.close();
        QFile::remove(path) ;
        return CBSTP_ARCHIVE_OK ;
    }
    m_current_page = abs(list[1].toInt(&ok)) ;
    //  Vérification de la validité de la valeur récupérée.
    if (m_current_page%m_number_pages_displayed != 0)
        m_current_page = m_current_page - m_current_page%m_number_pages_displayed ;



    //  Si on arrive ici c'est que le chargement s'est effectué correctement.
    file.close();
    return CBSTP_OK ;
}


void ComicBookSettings::saveSettings ()
{
    //  On ne sauvegarde les données que si le chemin vers l'archive est spécifié.
    if (m_path_to_archive.isEmpty())
        return ;

    //  Récupération du nom du Comic Book.
    QFileInfo comic_book_archive(m_path_to_archive) ;
    QString cb_name = comic_book_archive.baseName() ;

    //  Écriture des options.
    QString path = m_cbstp_folder + cb_name + ".cbstp" ;
    QFile file(path) ;
    file.open(QIODevice::WriteOnly | QIODevice::Text) ;

    QString line = "" ;
    //  Écriture de l'attribut "Archive".
    line = "Archive:" + m_path_to_archive + "\n" ;
    file.write(line.toStdString().c_str()) ;

    //  Écriture de l'attribut "ReadingStyle".
    line = "ReadingStyle:" + QString::number((int) m_reading_style) + "\n" ;
    file.write(line.toStdString().c_str()) ;

    //  Écriture de l'attribut "NumberPagesDisplayed".
    line = "NumberPagesDisplayed:" + QString::number(m_number_pages_displayed) + "\n" ;
    file.write(line.toStdString().c_str()) ;

    //  Écriture de l'attribut "CurrentPage".
    line = "CurrentPage:" + QString::number(m_current_page) + "\n" ;
    file.write(line.toStdString().c_str()) ;

    file.close() ;
}
