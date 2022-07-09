#include "P2PData.h"

using namespace Model;

P2PData::P2PData()
{

}


QList<P2PDataPair> P2PData::getData() const
{
    return m_dataPairList;
}
