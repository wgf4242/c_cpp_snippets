#include "plugin.h"
#include <windows.h>
#include <string>
#include <vector>

static int hMenuDumpSub;

enum {
    MENU_DUMP_MAIN,
    MENU_DUMP_AS_STRING,
    MENU_DUMP_AS_HEX_STRING,
    MENU_DUMP_AS_C_BYTE,
    MENU_DUMP_AS_C_WORD,
    MENU_DUMP_AS_C_DWORD,
    MENU_DUMP_AS_C_QWORD,
    MENU_DUMP_AS_PY_BYTE,
    MENU_DUMP_AS_PY_WORD,
    MENU_DUMP_AS_PY_DWORD,
    MENU_DUMP_AS_PY_QWORD
};

static void CopyToClipboard(const char* text)
{
    if (!OpenClipboard(NULL))
        return;

    EmptyClipboard();

    SIZE_T len = strlen(text);
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len + 1);
    if (hMem)
    {
        char* pMem = (char*)GlobalLock(hMem);
        if (pMem)
        {
            memcpy(pMem, text, len + 1);
            GlobalUnlock(hMem);
            SetClipboardData(CF_TEXT, hMem);
        }
    }

    CloseClipboard();
}

static std::vector<unsigned char> ReadMemory(duint start, duint end)
{
    std::vector<unsigned char> data;
    duint size = end - start + 1;
    data.resize(size);

    for (duint i = 0; i < size; i++)
    {
        unsigned char val = 0;
        if (DbgMemRead(start + i, &val, 1))
        {
            data[i] = val;
        }
        else
        {
            data[i] = 0;
        }
    }

    return data;
}

static void DumpAsString(const std::vector<unsigned char>& data)
{
    std::string output;
    for (unsigned char c : data)
    {
        if (c >= 32 && c <= 126)
        {
            output += c;
        }
        else
        {
            output += '.';
        }
    }

    _plugin_logprintf("[Dump] String: %s\n", output.c_str());
    CopyToClipboard(output.c_str());
    _plugin_logputs("[Dump] Copied to clipboard!");
}

static void DumpAsHexString(const std::vector<unsigned char>& data)
{
    std::string output;
    char buffer[4];
    for (unsigned char c : data)
    {
        sprintf_s(buffer, sizeof(buffer), "%02X ", c);
        output += buffer;
    }

    _plugin_logprintf("[Dump] Hex String: %s\n", output.c_str());
    CopyToClipboard(output.c_str());
    _plugin_logputs("[Dump] Copied to clipboard!");
}

static void DumpAsCArray(const std::vector<unsigned char>& data, int sizeType)
{
    const char* typeName = nullptr;
    const char* format = nullptr;
    int elementSize = 0;

    switch (sizeType)
    {
    case 1:
        typeName = "unsigned char";
        format = "0x%02X";
        elementSize = 1;
        break;
    case 2:
        typeName = "unsigned short";
        format = "0x%04X";
        elementSize = 2;
        break;
    case 4:
        typeName = "unsigned int";
        format = "0x%08X";
        elementSize = 4;
        break;
    case 8:
        typeName = "unsigned long long";
        format = "0x%016llX";
        elementSize = 8;
        break;
    }

    size_t count = data.size() / elementSize;
    std::string output;
    char buffer[32];
    sprintf_s(buffer, sizeof(buffer), "%s var[%zu] = {", typeName, count);
    output = buffer;

    for (size_t i = 0; i < count; i++)
    {
        if (i > 0)
        {
            output += ", ";
        }

        unsigned long long val = 0;
        for (int j = 0; j < elementSize; j++)
        {
            val |= ((unsigned long long)data[i * elementSize + j]) << (j * 8);
        }

        sprintf_s(buffer, sizeof(buffer), format, val);
        output += buffer;
    }
    output += "};";

    _plugin_logprintf("[Dump] %s\n", output.c_str());
    CopyToClipboard(output.c_str());
    _plugin_logputs("[Dump] Copied to clipboard!");
}

static void DumpAsPythonList(const std::vector<unsigned char>& data, int sizeType)
{
    const char* format = nullptr;
    int elementSize = 0;

    switch (sizeType)
    {
    case 1:
        format = "0x%02X";
        elementSize = 1;
        break;
    case 2:
        format = "0x%04X";
        elementSize = 2;
        break;
    case 4:
        format = "0x%08X";
        elementSize = 4;
        break;
    case 8:
        format = "0x%016llX";
        elementSize = 8;
        break;
    }

    size_t count = data.size() / elementSize;
    std::string output = "[";
    char buffer[32];

    for (size_t i = 0; i < count; i++)
    {
        if (i > 0)
        {
            output += ", ";
        }

        unsigned long long val = 0;
        for (int j = 0; j < elementSize; j++)
        {
            val |= ((unsigned long long)data[i * elementSize + j]) << (j * 8);
        }

        sprintf_s(buffer, sizeof(buffer), format, val);
        output += buffer;
    }
    output += "]";

    _plugin_logprintf("[Dump] %s\n", output.c_str());
    CopyToClipboard(output.c_str());
    _plugin_logputs("[Dump] Copied to clipboard!");
}

static void cbMenuDumpAsString()
{
    SELECTIONDATA sel;
    if (GuiSelectionGet(GUI_DUMP, &sel))
    {
        auto data = ReadMemory(sel.start, sel.end);
        DumpAsString(data);
    }
    else
    {
        _plugin_logputs("[Dump] Please select a region in Dump window!");
    }
}

static void cbMenuDumpAsHexString()
{
    SELECTIONDATA sel;
    if (GuiSelectionGet(GUI_DUMP, &sel))
    {
        auto data = ReadMemory(sel.start, sel.end);
        DumpAsHexString(data);
    }
    else
    {
        _plugin_logputs("[Dump] Please select a region in Dump window!");
    }
}

static void cbMenuDumpAsCByte()
{
    SELECTIONDATA sel;
    if (GuiSelectionGet(GUI_DUMP, &sel))
    {
        auto data = ReadMemory(sel.start, sel.end);
        DumpAsCArray(data, 1);
    }
    else
    {
        _plugin_logputs("[Dump] Please select a region in Dump window!");
    }
}

static void cbMenuDumpAsCWord()
{
    SELECTIONDATA sel;
    if (GuiSelectionGet(GUI_DUMP, &sel))
    {
        auto data = ReadMemory(sel.start, sel.end);
        DumpAsCArray(data, 2);
    }
    else
    {
        _plugin_logputs("[Dump] Please select a region in Dump window!");
    }
}

static void cbMenuDumpAsCDword()
{
    SELECTIONDATA sel;
    if (GuiSelectionGet(GUI_DUMP, &sel))
    {
        auto data = ReadMemory(sel.start, sel.end);
        DumpAsCArray(data, 4);
    }
    else
    {
        _plugin_logputs("[Dump] Please select a region in Dump window!");
    }
}

static void cbMenuDumpAsCQword()
{
    SELECTIONDATA sel;
    if (GuiSelectionGet(GUI_DUMP, &sel))
    {
        auto data = ReadMemory(sel.start, sel.end);
        DumpAsCArray(data, 8);
    }
    else
    {
        _plugin_logputs("[Dump] Please select a region in Dump window!");
    }
}

static void cbMenuDumpAsPyByte()
{
    SELECTIONDATA sel;
    if (GuiSelectionGet(GUI_DUMP, &sel))
    {
        auto data = ReadMemory(sel.start, sel.end);
        DumpAsPythonList(data, 1);
    }
    else
    {
        _plugin_logputs("[Dump] Please select a region in Dump window!");
    }
}

static void cbMenuDumpAsPyWord()
{
    SELECTIONDATA sel;
    if (GuiSelectionGet(GUI_DUMP, &sel))
    {
        auto data = ReadMemory(sel.start, sel.end);
        DumpAsPythonList(data, 2);
    }
    else
    {
        _plugin_logputs("[Dump] Please select a region in Dump window!");
    }
}

static void cbMenuDumpAsPyDword()
{
    SELECTIONDATA sel;
    if (GuiSelectionGet(GUI_DUMP, &sel))
    {
        auto data = ReadMemory(sel.start, sel.end);
        DumpAsPythonList(data, 4);
    }
    else
    {
        _plugin_logputs("[Dump] Please select a region in Dump window!");
    }
}

static void cbMenuDumpAsPyQword()
{
    SELECTIONDATA sel;
    if (GuiSelectionGet(GUI_DUMP, &sel))
    {
        auto data = ReadMemory(sel.start, sel.end);
        DumpAsPythonList(data, 8);
    }
    else
    {
        _plugin_logputs("[Dump] Please select a region in Dump window!");
    }
}

static bool cbExampleCommand(int argc, char** argv)
{
    if (argc < 3)
    {
        dputs("Usage: " PLUGIN_NAME "expr1, expr2");
        return false;
    }

    auto parseExpr = [](const char* expression, duint& value)
    {
        bool success = false;
        value = DbgEval(expression, &success);
        if (!success)
            dprintf("Invalid expression '%s'\n", expression);
        return success;
    };

    duint a = 0;
    if (!parseExpr(argv[1], a))
        return false;

    duint b = 0;
    if (!parseExpr(argv[2], b))
        return false;

    duint result = a + b;
    dprintf("$result = 0x%p + 0x%p = 0x%p\n", a, b, result);

    DbgValToString("$result", result);

    return true;
}

bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    dprintf("pluginInit(pluginHandle: %d)\n", pluginHandle);

    _plugin_registercommand(pluginHandle, PLUGIN_NAME, cbExampleCommand, true);

    return true;
}

PLUG_EXPORT void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
    switch (info->hEntry)
    {
    case MENU_DUMP_AS_STRING:
        cbMenuDumpAsString();
        break;
    case MENU_DUMP_AS_HEX_STRING:
        cbMenuDumpAsHexString();
        break;
    case MENU_DUMP_AS_C_BYTE:
        cbMenuDumpAsCByte();
        break;
    case MENU_DUMP_AS_C_WORD:
        cbMenuDumpAsCWord();
        break;
    case MENU_DUMP_AS_C_DWORD:
        cbMenuDumpAsCDword();
        break;
    case MENU_DUMP_AS_C_QWORD:
        cbMenuDumpAsCQword();
        break;
    case MENU_DUMP_AS_PY_BYTE:
        cbMenuDumpAsPyByte();
        break;
    case MENU_DUMP_AS_PY_WORD:
        cbMenuDumpAsPyWord();
        break;
    case MENU_DUMP_AS_PY_DWORD:
        cbMenuDumpAsPyDword();
        break;
    case MENU_DUMP_AS_PY_QWORD:
        cbMenuDumpAsPyQword();
        break;
    }
}

void pluginStop()
{
    dprintf("pluginStop(pluginHandle: %d)\n", pluginHandle);
}

void pluginSetup()
{
    _plugin_menuaddentry(hMenuDump, MENU_DUMP_AS_STRING, "Dump as string");
    _plugin_menuaddentry(hMenuDump, MENU_DUMP_AS_HEX_STRING, "Dump as hex string");
    _plugin_menuaddseparator(hMenuDump);
    _plugin_menuaddentry(hMenuDump, MENU_DUMP_AS_C_BYTE, "Dump as C/C++ array (BYTE)");
    _plugin_menuaddentry(hMenuDump, MENU_DUMP_AS_C_WORD, "Dump as C/C++ array (WORD)");
    _plugin_menuaddentry(hMenuDump, MENU_DUMP_AS_C_DWORD, "Dump as C/C++ array (DWORD)");
    _plugin_menuaddentry(hMenuDump, MENU_DUMP_AS_C_QWORD, "Dump as C/C++ array (QWORD)");
    _plugin_menuaddseparator(hMenuDump);
    _plugin_menuaddentry(hMenuDump, MENU_DUMP_AS_PY_BYTE, "Dump as python list (BYTE)");
    _plugin_menuaddentry(hMenuDump, MENU_DUMP_AS_PY_WORD, "Dump as python list (WORD)");
    _plugin_menuaddentry(hMenuDump, MENU_DUMP_AS_PY_DWORD, "Dump as python list (DWORD)");
    _plugin_menuaddentry(hMenuDump, MENU_DUMP_AS_PY_QWORD, "Dump as python list (QWORD)");
    dprintf("pluginSetup(pluginHandle: %d)\n", pluginHandle);
}
