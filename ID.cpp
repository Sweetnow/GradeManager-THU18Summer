#include "ID.h"

ID::ID() :isInit(false), hasWritten(false) {
}

ID::~ID() {
}

IDTYPE ID::sm_iFirstID = 10000000;

void ID::Write(std::ofstream& file)const {
    assert(isInit && file.is_open() && file.good());
    file.write((char*)&m_iID, sizeof(m_iID));
    file.write((char*)&isInit, sizeof(isInit));
    hasWritten = true;
}

void ID::Read(std::ifstream& file) {
    assert(file.is_open() && file.good());
    file.read((char*)&m_iID, sizeof(m_iID));
    file.read((char*)&isInit, sizeof(isInit));
}

IDTYPE ID::GetID()const {
    assert(isInit);
    return m_iID;
}