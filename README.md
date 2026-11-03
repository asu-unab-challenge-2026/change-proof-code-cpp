# Change-Proof Code
### Designing C++ That Survives New Requirements

A 90-minute team workshop for CS undergraduates (all years).
ASU School of Computing and Augmented Intelligence × Universidad Andrés Bello (UNAB).
Facilitator: Tejasvi Parupudi, PhD.

> Your code works. Every test passes. Then the requirement changes.
> Today your team ships that change without breaking what already works, and leaves evidence a teammate can trust.

---

## What you will practice

- Reading code you didn't write and spotting **why** it is hard to change
- Using **SOLID** principles as tools, not rules
- Writing **tests** that prove both the new behavior and the old one
- Giving and receiving a **code review**, the way industry teams do

No prior C++ or SOLID experience is required. First-years: your tests and questions count as much as code.

---

## 1. Get the code (pick one)

| Option | Needs | Best for |
| --- | --- | --- |
| **A. Codespaces** (browser, nothing to install) | A free GitHub account | Anyone without a C++ compiler |
| **B. Download ZIP** | Nothing | Anyone with a C++17 compiler installed |
| **C. Online compiler** | Nothing | Backup if A and B fail |

**A. Codespaces:** sign in to GitHub → green **Code** button → **Codespaces** tab → **Create codespace on main**. Wait about 2 minutes. The tests build and run automatically the first time. Stop the codespace when you finish (Codespaces page → ⋯ → Stop).

**B. Download ZIP:** green **Code** button → **Download ZIP** → unzip → open the folder in your editor (VS Code, CLion, Code::Blocks...). Or, with Git: `git clone <this repo's URL>`.

**C. Online compiler:** open [`single-file/campus_connect_all_in_one.cpp`](single-file/campus_connect_all_in_one.cpp) → copy everything → paste into an online C++17 compiler (for example OnlineGDB, choose language **C++17**) → Run.

> Want your own copy to push changes to? Click **Use this template** → **Create a new repository** (see [docs/GITHUB_QUICKSTART.md](docs/GITHUB_QUICKSTART.md)). Optional.

---

## 2. Build and run the tests

From the repo folder:

```bash
# Linux, macOS, Codespaces, or Windows with MinGW g++
g++ -std=c++17 -Wall -Wextra -Isrc -Itests src/*.cpp tests/*.cpp -o run_tests
./run_tests            # Windows: run_tests.exe
```

or with CMake:

```bash
cmake -S . -B build
cmake --build build
./build/run_tests      # Windows (Visual Studio): build\Debug\run_tests.exe
```

You should see:

```text
[PASS] books_an_available_seat_and_sends_one_confirmation
...
8 tests, 8 passed, 0 failed
```

Run the demo too: `g++ -std=c++17 -Isrc src/*.cpp app/main.cpp -o campus_demo && ./campus_demo`

---

## 3. The system: CampusConnect

CampusConnect is a fictional campus system where students register for events.

- A confirmed booking takes **one seat**. No overbooking.
- The same student can't book the same event twice.
- Unknown or full events are **rejected** and **no confirmation is sent**.
- After booking, the system sends a confirmation. If the provider does **not accept** it, the seat is kept and the confirmation is marked **pending**.
- Accepted is not the same as delivered.

## 4. Map of the repo

```text
src/
  models.hpp                 Attendee, Event, Booking, RegistrationResult
  registration_service.*     the heart of the system: works, but tangled  <- start here
  email_provider.*           simulated email vendor (no real email)
  sms_gateway.*              simulated SMS vendor, bought by IT, not used yet
  campus_admin_api.hpp       the admin interface (list, register, delete, export)
  kiosk.*                    the public lobby screen
app/main.cpp                 a short demo run
tests/
  baseline_tests.cpp         7 promises the system already keeps. Must keep passing.
  change_card_tests.cpp      YOUR tests for YOUR change card
  test_rig.hpp               the ONLY place tests know how the system is wired
  mini_test.hpp              tiny test helper (TEST_CASE, CHECK, CHECK_EQ)
single-file/                 everything in one file, for online compilers
TEAM.md                      your team worksheet (fill in and submit)
docs/                        SOLID cheat sheet, C++ bridge, GitHub quickstart
```

---

## 5. Your mission

| Minutes | What your team does |
| --- | --- |
| 0–8 | Form your team, pick roles: Product Owner, Designer, Driver, Tester |
| 8–18 | **Risk hunt:** run the tests; read `registerAttendee`; find 2 different reasons it might change; write 1 Given / When / Then test (TEAM.md §2) |
| 18–28 | Mini-lesson: SOLID in 10 minutes |
| 28–35 | **Design sketch:** draw the smallest useful design and one contract (TEAM.md §3) |
| 35–60 | **Change sprint:** open your change card, rotate roles, change the design, then the code; add at least 2 tests (TEAM.md §1, §4) |
| 60–70 | **Peer review:** swap with your partner team; give one specific comment; respond to the one you get (TEAM.md §5) |
| 70–82 | Demos: 30 s change · 45 s design and trade-off · 45 s test evidence |
| 82–90 | Submit ([SUBMISSION.md](SUBMISSION.md)) and fill in your individual exit ticket |

Your change card arrives at minute 35. Don't go looking for it in the code; it isn't there.

## 6. Rules of the game

1. **The 7 baseline tests must still pass.** They are promises users rely on.
2. You may change **how the system is wired** (`test_rig.hpp`, constructors, `main.cpp`).
   You may **not** change **what the baseline tests expect** (the Then lines).
3. Every new class or interface must point to a change you can name. More classes is not better design.
4. Label your evidence honestly: **run** (you saw it pass), **written** (code exists, not run), or **proposed** (described only).
5. Code is encouraged, not required. A clear design plus Given / When / Then tests earns full credit.
6. Using an AI assistant? Say so in TEAM.md §6, and make sure every teammate can explain the code.

## 7. Help

- [docs/SOLID_CHEATSHEET.md](docs/SOLID_CHEATSHEET.md): the five principles with CampusConnect examples
- [docs/CPP_BRIDGE.md](docs/CPP_BRIDGE.md): C++ for students coming from Python or Java, plus common compiler errors
- [docs/GITHUB_QUICKSTART.md](docs/GITHUB_QUICKSTART.md): your own copy, commits and pull requests (optional)
- [SUBMISSION.md](SUBMISSION.md): how to hand in your work

Stuck for more than 3 minutes? Raise a hand. Asking is a professional skill.

---

<sub>Original teaching material. CampusConnect, its people, emails and phone numbers are fictional. Code released under the MIT License (see LICENSE).</sub>
