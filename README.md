# Edger

**Edger** is a small Windows utility written in C++ that automates performing searches in Microsoft Edge. It was created to simulate random search activity.

> ⚠️ **Important:** This tool automates browser activity. Using automation to game Microsoft Rewards or other programs may violate their Terms of Service. Use this repository for learning and experimentation only and at your own risk.

---

## Repository Contents

* `Main.cpp` — main application entry and orchestration logic.
* `AutoClicker.cpp` / `AutoClicker.h` — helper code that simulates mouse/keyboard actions and simple navigation.
* `build.bat` — Windows batch script intended to build the project into `Edger.exe`.
* `Edger.exe` — prebuilt binary (if present).
* `testList.txt`, `chessplayers.txt` — example lists used by the program as search input.
* `icon.ico`, `icon.png` — optional icons used by the program.

---

## Requirements

* Windows 10/11
* Microsoft Edge installed
* A C++ compiler compatible with the project (MSVC / Visual Studio recommended).
* Administrator privileges may be required for simulated input on some systems.

---

## Build

To build from source on Windows, open a Command Prompt in the repository root and run:

```batch
build.bat
```

If `build.bat` uses `cl` (MSVC), make sure you have the "Developer Command Prompt for VS" or relevant environment set up. The script should compile the code and produce `Edger.exe` in the repository folder (or an `out`/`bin` folder if the script is configured that way).

---

## Usage

Run the compiled executable:

```batch
Edger.exe
```

By default the program will read keywords from bundled text files (e.g., `testList.txt` or `chessplayers.txt`) and perform searches in Edge according to the internal flow. If the program supports command line arguments or configuration, add details here (the project as-is does not include a config file).

---

## Configuration & Customization Ideas

If you want to make the utility easier to use or safer to test, consider adding:

* A `config.json` to control parameters such as search delay, number of searches, input file path, user-agent, and headless/display options.
* A `--dry-run` mode that prints planned actions instead of sending input to the system.
* Logging with timestamps to `Edger.log` so you can review what ran and when.
* Throttling and randomized delays between actions to more closely mimic human behavior (and further reduce risk of detection).

---

## Security & Safety Notes

* **Do not run untrusted binaries.** If you didn't build `Edger.exe` yourself, scan it and review the source before running.
* Automation that interacts with other services may be detected and can lead to account restrictions or bans.
* The repository does not include any tests or sandboxing — modify and test in a controlled environment.

---

## License

No license file was included in the original repository. If you own this repository or intend to publish it, add a LICENSE file (for example the MIT License) to clarify reuse permissions.

---

## Contributing

If you'd like help improving the project, I can:

* Add a polished README (this file).
* Add `config.json` support and a `--dry-run` flag.
* Create a safer demo mode that doesn't send input to the OS.
* Create a GitHub Actions CI job to build the project automatically.