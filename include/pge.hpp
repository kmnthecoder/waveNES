#include <iostream>
#include <sstream>

#include "bus.hpp"
#include "cpu.hpp"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Demo : public olc::PixelGameEngine
{
public:
	Demo() { sAppName = "NES Demo"; }

public:
	Bus nes;
	std::map<uint16_t, std::string> mapAsm;
	std::shared_ptr<Cartridge> cart;

	bool bEmulationRun = true;
	float fResidualTime = 0.0f;

	uint8_t selectedPalette = 0x00;

	std::string hex(uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	void DrawRam(int x, int y, uint16_t nAddr, int nRows, int nColumns)
	{
		int nRamX = x, nRamY = y;
		for (int row = 0; row < nRows; row++)
		{
			std::string sOffset = "$" + hex(nAddr, 4) + ":";
			for (int col = 0; col < nColumns; col++)
			{
				sOffset += " " + hex(nes.cpuRead(nAddr, true), 2);
				nAddr += 1;
			}
			DrawString(nRamX, nRamY, sOffset);
			nRamY += 10;
		}
	}

	void DrawCpu(int x, int y)
	{
		std::string status = "STATUS: ";
		DrawString(x, y, "STATUS:", olc::WHITE);
		DrawString(x + 64, y, "N", nes.cpu.p_flag & CPU::N ? olc::GREEN : olc::RED);
		DrawString(x + 80, y, "V", nes.cpu.p_flag & CPU::V ? olc::GREEN : olc::RED);
		DrawString(x + 96, y, "-", nes.cpu.p_flag & CPU::U ? olc::GREEN : olc::RED);
		DrawString(x + 112, y, "B", nes.cpu.p_flag & CPU::B ? olc::GREEN : olc::RED);
		DrawString(x + 128, y, "D", nes.cpu.p_flag & CPU::D ? olc::GREEN : olc::RED);
		DrawString(x + 144, y, "I", nes.cpu.p_flag & CPU::I ? olc::GREEN : olc::RED);
		DrawString(x + 160, y, "Z", nes.cpu.p_flag & CPU::Z ? olc::GREEN : olc::RED);
		DrawString(x + 178, y, "C", nes.cpu.p_flag & CPU::C ? olc::GREEN : olc::RED);
		DrawString(x, y + 10, "PC: $" + hex(nes.cpu.pc, 4));
		DrawString(x, y + 20, "A: $" + hex(nes.cpu.reg_a, 2) + "  [" + std::to_string(nes.cpu.reg_a) + "]");
		DrawString(x, y + 30, "X: $" + hex(nes.cpu.reg_x, 2) + "  [" + std::to_string(nes.cpu.reg_x) + "]");
		DrawString(x, y + 40, "Y: $" + hex(nes.cpu.reg_y, 2) + "  [" + std::to_string(nes.cpu.reg_y) + "]");
		DrawString(x, y + 50, "Stack P: $" + hex(nes.cpu.sp, 4));
	}

	void DrawCode(int x, int y, int nLines)
	{
		auto it_a = mapAsm.find(nes.cpu.pc);
		int nLineY = (nLines >> 1) * 10 + y;
		if (it_a != mapAsm.end())
		{
			DrawString(x, nLineY, (*it_a).second, olc::CYAN);
			while (nLineY < (nLines * 10) + y)
			{
				nLineY += 10;
				if (++it_a != mapAsm.end())
				{
					DrawString(x, nLineY, (*it_a).second);
				}
			}
		}

		it_a = mapAsm.find(nes.cpu.pc);
		nLineY = (nLines >> 1) * 10 + y;
		if (it_a != mapAsm.end())
		{
			while (nLineY > y)
			{
				nLineY -= 10;
				if (--it_a != mapAsm.end())
				{
					DrawString(x, nLineY, (*it_a).second);
				}
			}
		}
	}

	bool OnUserCreate(const char *filepath)
	{
		//filepath = "../nestest.nes";

		std::cout << "--- Attempting to load: " << filepath << " ---" << std::endl;

		cart = std::make_shared<Cartridge>(filepath);

		if (!cart->ImageValid())
		{
			return false;
		}

		// Insert into NES
		nes.insertCartridge(cart);

		// Extract dissassembly
		mapAsm = nes.cpu.disassemble(0x0000, 0xFFFF);

		// Reset NES
		nes.reset();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{
		Clear(olc::VERY_DARK_MAGENTA);

		nes.controller[0] = 0x00;
		nes.controller[0] |= GetKey(olc::Key::A).bHeld ? 0x80 : 0x00; // a
		nes.controller[0] |= GetKey(olc::Key::S).bHeld ? 0x40 : 0x00; // b
		nes.controller[0] |= GetKey(olc::Key::Z).bHeld ? 0x10 : 0x00; // start
		nes.controller[0] |= GetKey(olc::Key::X).bHeld ? 0x20 : 0x00; // select
		nes.controller[0] |= GetKey(olc::Key::UP).bHeld ? 0x08 : 0x00;
		nes.controller[0] |= GetKey(olc::Key::DOWN).bHeld ? 0x04 : 0x00;
		nes.controller[0] |= GetKey(olc::Key::LEFT).bHeld ? 0x02 : 0x00;
		nes.controller[0] |= GetKey(olc::Key::RIGHT).bHeld ? 0x01 : 0x00;

		if (GetKey(olc::Key::SPACE).bPressed)
			bEmulationRun = !bEmulationRun;
		if (GetKey(olc::Key::R).bPressed)
			nes.reset();
		if (GetKey(olc::Key::P).bPressed)
			(++selectedPalette) &= 0x07;

		if (bEmulationRun)
		{
			if (fResidualTime > 0.0f)
				fResidualTime -= fElapsedTime;
			else
			{
				fResidualTime += (1.0f / 60.0f) - fElapsedTime;
				do
				{
					nes.tick();
				} while (!nes.ppu.frameComplete);
				nes.ppu.frameComplete = false;
			}
		}
		else
		{
			// Emulate code step-by-step
			if (GetKey(olc::Key::C).bPressed)
			{
				// Clock enough times to execute a whole CPU instruction
				do
				{
					nes.tick();
				} while (!nes.cpu.complete());
				// CPU clock runs slower than system clock, so it may be
				// complete for additional system clock cycles. Drain
				// those out
				do
				{
					nes.tick();
				} while (nes.cpu.complete());
			}

			// Emulate one whole frame
			if (GetKey(olc::Key::F).bPressed)
			{
				// Clock enough times to draw a single frame
				do
				{
					nes.tick();
				} while (!nes.ppu.frameComplete);
				// Use residual clock cycles to complete current instruction
				do
				{
					nes.tick();
				} while (!nes.cpu.complete());
				// Reset frame completion flag
				nes.ppu.frameComplete = false;
			}
		}

		DrawCpu(516, 2);
		DrawCode(516, 72, 24);

		// Draw OAM Contents (first 26 out of 64) ======================================
		/*
		for (int i = 0; i < 26; i++)
		{
			std::string s = hex(i, 2) + ": (" + std::to_string(nes.ppu.pOAM[i * 4 + 3]) + ", " + std::to_string(nes.ppu.pOAM[i * 4 + 0]) + ") " + "ID: " + hex(nes.ppu.pOAM[i * 4 + 1], 2) +
							+" AT: " + hex(nes.ppu.pOAM[i * 4 + 2], 2);
			DrawString(516, 72 + i * 10, s);
		}
		*/

		// Draw Palettes & Pattern Tables ==============================================
		const int nSwatchSize = 6;
		for (int p = 0; p < 8; p++)		// For each palette
			for (int s = 0; s < 4; s++) // For each index
				FillRect(516 + p * (nSwatchSize * 5) + s * nSwatchSize, 340,
						 nSwatchSize, nSwatchSize, nes.ppu.GetColourFromPaletteRam(p, s));

		// Draw selection reticule around selected palette
		DrawRect(516 + selectedPalette * (nSwatchSize * 5) - 1, 339, (nSwatchSize * 4), nSwatchSize, olc::WHITE);

		DrawSprite(516, 348, &nes.ppu.GetPatternTable(0, selectedPalette));
		DrawSprite(648, 348, &nes.ppu.GetPatternTable(1, selectedPalette));

		DrawSprite(0, 0, &nes.ppu.GetScreen(), 2);

		return true;
	}
};