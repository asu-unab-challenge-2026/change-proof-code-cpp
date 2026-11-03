# SOLID cheat sheet (CampusConnect edition)

SOLID is five questions to ask **when a real change arrives**. Start from the change, not the letter.

| Letter | The question it asks | In CampusConnect today | Common misreading |
| --- | --- | --- | --- |
| **S** Single responsibility | Does this code change for more than one group of people? | `registerAttendee` changes when the events office changes seat rules, when communications changes the wording, and when IT changes the email vendor. | "One method per class." No: one *reason to change* per unit. |
| **O** Open/closed | Can I add a known kind of variation by **adding** code instead of editing the core? | Adding SMS means editing `registerAttendee`, because it creates `EmailProvider` itself. | "Never edit code." No: you still edit setup code and fix bugs. |
| **L** Liskov substitution | Does every implementation keep the promise callers rely on? | `EmailProvider::send()` returns `true` during an outage, even though nothing was accepted. It compiles; it still lies. | "Only about inheritance syntax." No: it's about **behavior**. |
| **I** Interface segregation | Does each client depend only on what it uses? | The read-only `Kiosk` depends on `CampusAdminAPI`, which can also delete events and export emails. | "It's a security feature." No: you still need real permissions on the server. |
| **D** Dependency inversion | Do the business rules depend on contracts, with concrete tools plugged in from outside? | The booking rules construct `EmailProvider` directly, so tests can't swap in a fake. | "You need a DI framework." No: a constructor parameter is enough. |

## Which principle for which change?

| If the change is about... | Look first at | Typical move |
| --- | --- | --- |
| Different people asking for different edits in one function | S | Extract the part that changes for the other group (e.g., a formatter) |
| A new **kind** of something you already have (channel, format, payment) | O + D | Define a contract; add a new implementation; choose it at setup |
| An implementation that "works" but surprises its callers | L | Write the contract down; make every implementation keep it; test all of them with one test |
| A client that can call far more than it needs | I | Give it a small role interface; let a bigger class implement several |
| Code you can't test without the network, a database or the clock | D | Pass the dependency in; use a fake in tests |

## The C++ shape of a contract

```cpp
// A contract: what any notifier promises.
class Notifier {
public:
    virtual ~Notifier() = default;                       // safe cleanup through a base pointer
    // Returns true ONLY if a provider accepted the message. Never lies.
    virtual bool notify(const Attendee& to, const std::string& text) = 0;   // pure virtual
};

// One implementation (an adapter around a vendor SDK).
class EmailNotifier : public Notifier {
public:
    bool notify(const Attendee& to, const std::string& text) override {
        return provider_.send(to.email, text);
    }
private:
    EmailProvider provider_;
};

// The rules receive the contract from outside (constructor injection).
class RegistrationService {
public:
    explicit RegistrationService(Notifier& notifier) : notifier_(notifier) {}
private:
    Notifier& notifier_;
};
```

## Before you add a class, ask

1. Which **change card** does this seam help with? (No card, no seam.)
2. Could a **function** do the job instead of a class hierarchy?
3. What does the extra structure **cost** a new teammate reading the code?

## Further reading

- Robert C. Martin, *Design Principles and Design Patterns* (2000): the original discussion of these principles.
- Barbara Liskov and Jeannette Wing, *A Behavioral Notion of Subtyping* (1994): where "L" comes from.
- GitHub Docs, *About pull requests*: how review works on real teams.
