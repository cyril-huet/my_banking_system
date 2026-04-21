# 💳 My Banking System

A simple banking system written in **C**, using:
- PostgreSQL (Supabase)
- Custom HTTP server
- Minimal web interface

---

## 🚀 Features

- Create account
- Login
- Check balance
- Deposit money
- Withdraw money
- Transfer money

---

## 🛠️ Tech Stack

- C (low-level backend)
- libpq (PostgreSQL client)
- CivetWeb (embedded HTTP server)
- HTML (frontend)

---

## 📂 Project Structure
```sh
.
├── include/ # Headers
├── lib/ # External libs (CivetWeb)
├── src/ # Source code
├── web/ # Frontend
├── Makefile
```


---



## ⚙️  Installation

### macOS (Homebrew)

```sh
brew install libpq
```
### Linux
```sh
sudo apt install libpq-dev
```

## 🔨 Build
```sh
make
```

## ▶️  Run
### Run the executable:
```sh
./server
```
### Open your browser:

```sh
http://localhost:8080
```

## 🎮 API Examples
```sh
/login?id=1&password=1234
/balance?id=1
/deposit?id=1&amount=100
/withdraw?id=1&amount=50
/transfer?from=1&to=2&amount=25
/create?id=2&password=abcd
```

## 🧹 Format code
```sh
make format
```


## ⚠️  Notes
Uses a remote PostgreSQL database (Supabase)

No authentication security (educational project)

Passwords are stored in plain text ⚠️

## 👨‍💻 Author
Cyril HUET
