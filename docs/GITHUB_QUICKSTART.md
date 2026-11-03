# GitHub quickstart (optional)

You don't need GitHub to take part. If someone on your team has an account, this is how real teams work, and it gives you the best way to submit.

## 1. Make your team's copy

1. Sign in to GitHub and open this repo.
2. Click **Use this template** → **Create a new repository**.
3. Name it `cpc-T03-cardC` (your team number and card), choose **Public**, click **Create repository**.
4. Add teammates who have accounts: your repo → **Settings** → **Collaborators** → **Add people**.

## 2. Open it in Codespaces

Your repo → green **Code** button → **Codespaces** → **Create codespace on main**.
When it opens, the tests build and run in the terminal. To run them again:

```bash
g++ -std=c++17 -Wall -Wextra -Isrc -Itests src/*.cpp tests/*.cpp -o run_tests && ./run_tests
```

## 3. Work on a branch, then commit

```bash
git switch -c card-c-outage                  # a branch named after your change
# ... edit code and tests ...
./run_tests > test_output.txt                # save your evidence
git add -A
git commit -m "Keep the booking and mark pending when email is down"
git push -u origin card-c-outage
```

Commit message = what the change does, in the present tense, like a pull-request title.

You can also use the **Source Control** panel in VS Code: stage (+), type a message, **Commit**, **Sync**.

## 4. Open a pull request for peer review

1. Your repo → **Pull requests** → **New pull request** → base: `main`, compare: your branch.
2. Title: verb + behavior (same as TEAM.md §5). Description: problem, resulting behavior, evidence.
3. Your reviewer team leaves comments in **Files changed** (they need a GitHub account), or reviews on paper.
4. Reply to each comment, push a fix if needed, then **Merge**.

## 5. Check the robot

Every push runs the tests on GitHub (**Actions** tab). A green check means the tests passed on a clean machine, which is strong evidence for your demo.

## Stop your codespace

github.com/codespaces → ⋯ next to your codespace → **Stop codespace**. Free hours are limited each month.
