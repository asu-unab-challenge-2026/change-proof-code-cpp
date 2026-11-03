# How to submit

**One submission per team, before the workshop ends (minute 88).**
You may edit your submission until 23:59 the same day. The last version is the one reviewed.

Your facilitator shares the **submission form** link (QR code on the last slides). Pick ONE path:

| Path | Use it if | You submit |
| --- | --- | --- |
| 1. GitHub link (preferred) | Someone on your team has a GitHub account | The URL of your team's public repo |
| 2. Zip upload | Nobody has GitHub, or GitHub gave you trouble | One `.zip` file, max 10 MB |
| 3. Paper only | Your laptops failed | Photos of your printed worksheet pages |

Every path also asks for: team number, change card, members (name, year, email), your evidence status, your test output, your pull-request title, and the review comment you received.

---

## Path 1: GitHub link

1. On this repo's page, click **Use this template** → **Create a new repository**.
2. Owner: your account. Name: `cpc-T03-cardC` (your team number and card). Visibility: **Public**.
3. Make your changes in a Codespace (or locally) and push them. See [docs/GITHUB_QUICKSTART.md](docs/GITHUB_QUICKSTART.md).
4. Check that the **Actions** tab shows a green check (tests passed on GitHub).
5. Paste the repo URL into the form.

## Path 2: Zip upload

Name the file `T<team>_<card>_change-proof-code.zip`, for example `T03_C_change-proof-code.zip`.

```text
T03_C_change-proof-code.zip
└── T03_C_change-proof-code/
    ├── TEAM.md               required: your filled-in team worksheet
    ├── test_output.txt       required: paste of your last test run, or the words "not run"
    ├── src/                  your changed code
    ├── tests/                baseline tests + your change-card tests
    ├── app/                  only if you changed main.cpp
    ├── single-file/          only if you worked in an online compiler
    └── worksheet_photos/     optional: photos of paper pages
```

Leave out: `build/`, `.exe` files, `.vscode/`, `.git/`.

How to make the zip:

- **Windows:** right-click the folder → **Send to** → **Compressed (zipped) folder** → rename.
- **macOS:** right-click the folder → **Compress** → rename.
- **Codespaces / Linux:** in the terminal, from the repo folder:
  ```bash
  ./run_tests > test_output.txt   # or: ./build/run_tests > test_output.txt
  zip -r T03_C_change-proof-code.zip . -x "build/*" ".git/*" "*.zip" "run_tests" "campus_demo"
  ```
  then right-click the zip in the file explorer → **Download**.
- **Online compiler:** copy your edited code into `single-file/campus_connect_all_in_one.cpp`, and paste the output into `test_output.txt`.

## Path 3: Paper only

Photograph worksheet pages 1–4 (all text readable, one page per photo) and upload them in the form.

---

## Checklist before you press Submit

- [ ] TEAM.md has every section filled in, including roles
- [ ] The 7 baseline tests still pass, or you wrote "not run" honestly
- [ ] At least 2 tests for your change card (code, or Given / When / Then in TEAM.md §4)
- [ ] Your peer-review comment and your response are in TEAM.md §5
- [ ] Every member's name is on the submission
