# OpenJK for iOS (owner's fork): notes for Claude Code sessions

The owner's fork of Nodman/OpenJK-iOS, itself a fork of JACoders/OpenJK: Jedi
Academy (single player and multiplayer) on iPhone and iPad, with Jedi Outcast
single player planned. The owner plays on an iPhone, isn't a programmer, and reads
everything on a phone.

- **Build branch:** `ios`. `master` is the original author's README branch; leave it.
- **Upstreams:** `Nodman/OpenJK-iOS` (`ios`) and `JACoders/OpenJK` (`master`). Merge
  from them; never rewrite their history.
- **iOS code:** `shared/sys/ios/` (platform, touch, gamepad, assets),
  `shared/ios/touch/` (button art), `cmake/Modules/OpenJKiOS*.cmake`, `cmake/ios/`
  (Info.plist, icons, gl4es/ANGLE patches), `scripts/ios/`, tests in `tests/ios/`.
  Engine hooks are spread over `code/` (JA SP, also the JO SP engine with
  `JK2_MODE`), `codemp/` (JA MP) and `shared/`. `codeJK2/` (JO's game code) has no
  iOS changes yet, and `CMakePresets.json` builds JO off.
- **CI:** `.github/workflows/ios.yml`, Xcode 26. A push to `ios` builds unsigned IPAs
  (no release). A pushed `ios-v*` tag makes a public release, so never push tags.
  `scripts/build-ios.sh` refuses the iOS 27 SDK until SDL2 gets its UIScene patch.
- **Bundle ids** are still the original author's (`org.openjk.ios.sp` / `.mp`).

## Rules

- Follow the owner's house style (`docs/HOUSE_STYLE.md` in the private files repo,
  `sithewok13-dev/jk-files`) and the rules in their other ports' CLAUDE.md files:
  the touch controls standard, no game data anywhere public, commits as
  `Claude <noreply@anthropic.com>` with subject `iOS: ...`, no PRs unless asked,
  releases only after a preview and the owner's explicit go.
- **Game data:** never commit, upload, bundle or publish the game's files (`.pk3`
  assets, installers, extracted folders). Local copies only.
- **Talking to the owner:** plain words, short messages, direct links, honesty about
  what was and wasn't tested.
