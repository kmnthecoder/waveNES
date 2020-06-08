#include "cartridge.hpp"
#include "bus.hpp"

#include <fstream>

Cartridge::Cartridge(const std::string &file)
{
    // iNES format
    struct HeaderStruct
    {
        char name[4];
        uint8_t prg_chunks;
        uint8_t chr_chunks;
        uint8_t mapper1;
        uint8_t mapper2;
        uint8_t prg_ram_size;
        uint8_t tvSys1;
        uint8_t tvSys2;
        char unused[5];
    } header;

    std::ifstream fileStream;
    fileStream.open(file, std::ifstream::binary);
    if (fileStream.is_open())
    {
        // read file headewr
        fileStream.read((char *)&header, sizeof(HeaderStruct));

        if (header.mapper1 & 0x04)
        {
            fileStream.seekg(512, std::ios_base::cur);
        }

        // mapper id
        mapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);

        uint8_t fileType = 1;

        if (fileType == 0)
        {
        }

        if (fileType == 1)
        {
            PRGBanks = header.prg_chunks;
            PRGMemory.resize(PRGBanks * 16384);
            fileStream.read((char *)PRGMemory.data(), PRGMemory.size());

            CHRBanks = header.chr_chunks;
            CHRMemory.resize(CHRBanks * 8192);
            fileStream.read((char *)CHRMemory.data(), CHRMemory.size());
        }

        if (fileType == 2)
        {
        }

        switch (mapperID)
        {
        case 0:
            mapper = std::make_shared<Mapper0>(PRGBanks, CHRBanks);
            break;
        }

        fileStream.close();
    }
}

Cartridge::~Cartridge() {}

bool Cartridge::cpuRead(int16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;
    if (mapper->cpuMapRead(addr, mapped_addr))
    {
        data = PRGMemory[mapped_addr];
        return true;
    }
    else
    {
        return false;
    }
}
bool Cartridge::cpuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;
    if (mapper->cpuMapWrite(addr, mapped_addr))
    {
        PRGMemory[mapped_addr] = data;
        return true;
    }
    else
    {
        return false;
    }
}

bool Cartridge::ppuRead(int16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;
    if (mapper->cpuMapRead(addr, mapped_addr))
    {
        data = CHRMemory[mapped_addr];
        return true;
    }
    else
    {
        return false;
    }
}
bool Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;
    if (mapper->cpuMapRead(addr, mapped_addr))
    {
        CHRMemory[mapped_addr] = data;
        return true;
    }
    else
    {
        return false;
    }
}