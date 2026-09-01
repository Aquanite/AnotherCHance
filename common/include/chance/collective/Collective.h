#ifndef CHANCE_COLLECTIVE_COLLECTIVE_H
#define CHANCE_COLLECTIVE_COLLECTIVE_H

/*
COLLECTIVE is the container format used to store CHance IL (CEIL) binary programs/libraries.

The format is as specified:
HEADER:
4 bytes magic 0x0C011EC1
4 bytes language version
(n amount of sections, all sizeof(CollectiveSection) + extra bytes that are included in said section.)
(section header ends with 8 bytes dictating the next offset)
End section, the last section in a binary that defines any extra data used by said sections I.E reflection data, or large structures.
Other sections may leave a pointer (offset + start) to data in this section
*/

#include <chance/assert.h>
#include <chance/target/system.h>
#include <chance/types/generic/NativeArray.h>
#include <chance/types/qad.h>
#include <cstdint>

#define CHANCE_COLLECTIVE_MAGIC   0x0C011EC1
#define CHANCE_COLLECTIVE_SECTION_MAGIC 0x00CEC0DE
#define CHANCE_COLLECTIVE_VERSION 0x00000001

namespace CE::Collective
{
    enum_t SectionType : uint16_t
    {
        Header          = 0xCE25, // Reference to CHance's H25 version that never got officially named.
        CompilerInfo    = 0x14F0,
        Module          = 0xC0DE,
        Debug           = 0xDEB5,
        End             = 0x0B1E, // Doesn't really need its own, only really is a marker. (OH, BYE)
    };

    struct Section
    {
        uint32_t Magic; // 0x00CEC0DE CE CODE, (Reference to the old bytecode CHance Code)
        SectionType Type;
        uint64_t OffsetOfNext; // Start of file + OffsetOfNext == next section
    };

    struct CompilerInfoSection : Section
    {
        uint32_t CompilerVersion;
        const char* CompilerName;
        const char* Language;
        const char* LanguageVersion;
    };

    struct HeaderSection : Section
    {
        uint32_t Version;
        uint64_t SectionCount;
    };

    struct EndSection : Section
    {
        CENative DataLength;
    };

    class Collective
    {
    public:
        NativeArray<Section> Sections;

    public:
        void Save(uint8_t*& data, CENative& length)
        {
            CE_ASSERT(Sections.Length(), "Length of collective sections cannot be zero!");

            for (CENative i = 0; i < Sections.Length(); i++)
            {
                length += GetSectionLength(Sections[i]);
            }

            CE_NOTIMPL();

            (void)data;

            // TODO: actually flatten the sections & turn pointers into offsets 
        }

        void Load(uint8_t* data, CENative length)
        {
            uint64_t last = 0;
        #ifdef VDEBUG
            CHANCE_PRINT("Loading Collective...\n");
        #endif // VDEBUG

            CE_ASSERT(data, "Collective binary is NULL");
            CE_ASSERT(length > sizeof(HeaderSection), "Collective binary is too small to be valid");

            Section* initSec = reinterpret_cast<Section*>(data);

            AssertSection(initSec, SectionType::Header);

            HeaderSection* hdr = static_cast<HeaderSection*>(initSec);

            CE_ASSERT(hdr->SectionCount > 1, "Too little sections to be a valid Collective binary");
            CE_ASSERT(hdr->OffsetOfNext > sizeof(HeaderSection), "Invalid offset from header in Collective binary");

            Sections.Add(*initSec);

        #ifdef VDEBUG
            CHANCE_PRINT("Loaded Header:\n- CEIL Version: %8X\n", hdr->Version);
        #endif // VDEBUG

            uint8_t* current = data;
            CENative max = reinterpret_cast<CENative>(data + length);
            bool hitEnd = false;

            while (current < data + length)
            {
                Section* currentSection = reinterpret_cast<Section*>(current);

                AssertSection(currentSection);

                if (currentSection->Type == SectionType::End)
                {
                    hitEnd = true;
                    break;
                }

                // TODO: Other sections
                CE_NOTIMPL();

                CE_ASSERT(currentSection->OffsetOfNext > last, "Collective binary tried to jump to a section aleady parsed");
                CE_ASSERT(currentSection->OffsetOfNext < max, "Collective binary tried to jump to a section out of memory bounds");

                current = data + currentSection->OffsetOfNext;
                last = currentSection->OffsetOfNext;
            }

            CE_ASSERT(hitEnd, "Did not reach a valid END section in the Collective binary");
        }
    
    private:
        void AssertSection(Section* sect, SectionType type)
        {
            CE_ASSERT(sect, "Section is NULL in Collective binary");
            CE_ASSERT(sect->Magic == CHANCE_COLLECTIVE_SECTION_MAGIC, "Type is not a Section in Collective binary");
            CE_ASSERT(sect->Type == type, "Not the expected section type in Collective binary");
        }

        void AssertSection(Section* sect)
        {
            CE_ASSERT(sect, "Section is NULL in Collective binary");
            CE_ASSERT(sect->Magic == CHANCE_COLLECTIVE_SECTION_MAGIC, "Type is not a Section in Collective binary");
        }
        
        CENative GetSectionLength(Section sect)
        {
            switch (sect.Type)
            {
                case SectionType::Header:       return sizeof(HeaderSection);
                case SectionType::CompilerInfo: return sizeof(CompilerInfoSection);
                case SectionType::Module:       CE_NOTIMPL();
                case SectionType::Debug:        CE_NOTIMPL();
                case SectionType::End:          return static_cast<EndSection>(sect).DataLength;
            }

            CE_FAIL("Section does not exist!");
        }
    };
};

#endif // CHANCE_COLLECTIVE_COLLECTIVE_H