#include "playlistmanager.h"

#include "plsparser.h"
#include <QDebug>

PlaylistManager::PlaylistManager(QObject *parent, QSparqlConnection *connection) :
    QObject(parent)
{
    if ( connection != 0  ) {
        mSparQLConnection = connection;
    }
    mTracksModel = 0;
    mThread = new QThread();
    mThread->start();
}


void PlaylistManager::requestPlaylist(QString url)
{
    qDebug() << "Playlist requested: " << url;
    // Check which ending
    if ( url.toLower().endsWith(".pls")  ) {
        QList<QUrl> *urls;

        qDebug() << "requested PL is an PLS list";
        PLSParser plsParser;
        urls = plsParser.parsePlaylist(url);

//        if ( mTracksModel != 0 ) {
//            delete(mTracksModel);
//            mTracksModel = 0;
//        }
        mTracksModel = new SavedPlaylistTracksModel(0,urls,mSparQLConnection,mThread);
        emit playlistTracksReady(mTracksModel);
    }
}
