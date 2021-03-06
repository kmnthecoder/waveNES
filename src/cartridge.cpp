#include "cartridge.hpp"

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

    bImageValid = false;

    std::ifstream fileStream;
    fileStream.open(file, std::ifstream::binary);
    if (fileStream.is_open())
    {
        // read file header
        fileStream.read((char *)&header, sizeof(HeaderStruct));

        if (header.mapper1 & 0x04)
        {
            fileStream.seekg(512, std::ios_base::cur);
        }

        // mapper id
        mapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
        mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;

        // file format
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

            if (CHRBanks == 0)
            {
                // create CHR ram
                CHRMemory.resize(8192);
            }
            else
            {
                // allocate for ROM
                CHRMemory.resize(CHRBanks * 8192);
            }
            fileStream.read((char *)CHRMemory.data(), CHRMemory.size());
        }

        if (fileType == 2)
        {
        }

        // load correct mapper
        switch (mapperID)
        {
        case 0:
            mapper = std::make_shared<Mapper0>(PRGBanks, CHRBanks);
            break;
        }

        bImageValid = true;
        fileStream.close();
    }
}

Cartridge::~Cartridge() {}

bool Cartridge::cpuRead(uint16_t addr, uint8_t &data)
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
    if (mapper->cpuMapWrite(addr, mapped_addr, data))
    {
        PRGMemory[mapped_addr] = data;
        return true;
    }
    else
    {
        return false;
    }
}

bool Cartridge::ppuRead(uint16_t addr, uint8_t &data)
{
    uint32_t mapped_addr = 0;
    if (mapper->ppuMapRead(addr, mapped_addr))
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
    if (mapper->ppuMapRead(addr, mapped_addr))
    {
        CHRMemory[mapped_addr] = data;
        return true;
    }
    else
    {
        return false;
    }
}

bool Cartridge::ImageValid()
{
    return bImageValid;
}

void Cartridge::reset()
{
    // resets mapper, not ROM contents
    if (mapper != nullptr)
    {
        mapper->reset();
    }
}