# C++ bridge: for students coming from Python or Java

You only need a little C++ today. This page covers exactly that little.

## Files: `.hpp` and `.cpp`

- A **header** (`.hpp`) declares what exists: classes, function signatures. Others `#include` it.
- A **source file** (`.cpp`) defines how it works.
- `#pragma once` at the top of a header stops it from being included twice.

## Classes and structs

```cpp
struct Event {             // struct: members are public by default (plain data)
    std::string id;
    std::string title;
    int capacity = 0;
};

class Kiosk {              // class: members are private by default
public:
    explicit Kiosk(CampusAdminAPI& api);   // constructor
    std::string render() const;            // const = does not modify the object
private:
    CampusAdminAPI& api_;                  // trailing _ = member variable (a convention)
};
```

## References: `&` and `const&`

| You write | Meaning | Python / Java feel |
| --- | --- | --- |
| `Event e` | a copy | a new object |
| `Event& e` | the caller's object, can modify it | passing an object reference |
| `const Event& e` | the caller's object, read-only, no copy | the usual way to pass strings and objects |

A reference can never be null and always refers to the same object.

## Interfaces in C++

C++ has no `interface` keyword. A class with only **pure virtual** functions plays that role:

```cpp
class EventReader {
public:
    virtual ~EventReader() = default;                        // 1. virtual destructor
    virtual std::vector<EventSummary> listEvents() const = 0; // 2. "= 0" means: must be implemented
};

class FixedEventReader : public EventReader {                // 3. public inheritance
public:
    std::vector<EventSummary> listEvents() const override {  // 4. override: compiler checks the match
        return events_;
    }
private:
    std::vector<EventSummary> events_;
};
```

Java equivalent: `interface EventReader { List<EventSummary> listEvents(); }` and `class FixedEventReader implements EventReader`.
Python equivalent: an `abc.ABC` with an `@abstractmethod`.

## Passing a dependency in (constructor injection)

```cpp
class RegistrationService {
public:
    RegistrationService(Notifier& notifier) : notifier_(notifier) {}  // member initializer list
private:
    Notifier& notifier_;
};

// Somewhere else (main.cpp or test_rig.hpp) - the "composition root":
EmailNotifier email;
RegistrationService service(email);   // the service never knows it's email
```

The object you pass must live at least as long as the service using it. In `test_rig.hpp`, declare members in the order they are needed: dependencies first, the service last.

## Strings and vectors

```cpp
std::string text = "You are booked for " + event.title + ".";
std::vector<Booking> bookings;
bookings.push_back({"s-1001", "robotics-night", true});
for (const Booking& b : bookings) { /* read each one */ }
```

## Compiler errors you may meet today

| Error message (g++) | Usually means | Fix |
| --- | --- | --- |
| `cannot declare variable 'x' to be of abstract type` | You didn't implement every `= 0` function | Implement the missing function; check spelling and `const` |
| `'...' marked 'override', but does not override` | Your signature differs from the base (often a missing `const`) | Copy the exact signature from the interface |
| `undefined reference to ...` | A `.cpp` file wasn't compiled | Use `src/*.cpp` in the command, or re-run CMake |
| `no matching function for call to 'RegistrationService::RegistrationService()'` | You added constructor parameters | Update the wiring in `tests/test_rig.hpp` and `app/main.cpp` |
| `'X' was not declared in this scope` | Missing `#include` or namespace | Include the header; write `campus::X` |
| `invalid use of incomplete type` | Only a forward declaration was visible | Include the full header in the `.cpp` |

## Visual Studio (MSVC) users

Use CMake, or this from a *Developer Command Prompt*:
`cl /std:c++17 /EHsc /utf-8 /Isrc /Itests src\*.cpp tests\*.cpp /Fe:run_tests.exe`
