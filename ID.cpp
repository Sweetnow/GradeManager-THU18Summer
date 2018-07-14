#include "ID.h"

ID::ID() {
}

ID::~ID() {
}


void ID::Write(std::ofstream& file) {
    assert(isInit && file.is_open() && file.good());
    file.write((char*)&m_iID, sizeof(m_iID));
    file.write((char*)&isInit, sizeof(isInit));
}

void ID::Read(std::ifstream& file) {
    assert(file.is_open() && file.good());
    file.read((char*)&m_iID, sizeof(m_iID));
    file.read((char*)&isInit, sizeof(isInit));
}

IDTYPE ID::GetID() {
    assert(isInit);
    return m_iID;
}