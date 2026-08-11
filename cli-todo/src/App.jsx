import { useEffect, useState } from 'react'
import './App.css'
import img1 from './assets/img1.png'
import img2 from './assets/img2.png'
import img3 from './assets/img3.png'

function Navbar({ now }){
  return (
  <header className="w-full py-4 px-6 md:px-12 flex items-center justify-between bg-transparent">
      <div className="flex items-center gap-3">
  <div className="w-10 h-10 rounded-md bg-indigo-600 flex items-center justify-center text-sm font-bold text-white shadow-xl">CLI</div>
        <div>
          <div className="font-extrabold text-white text-lg">cli-todo</div>
          <div className="text-xs text-indigo-300">Lightweight terminal-first todo</div>
        </div>
      </div>

      <div className="text-right">
        <div className="text-sm text-indigo-300">{now.date}</div>
        <div className="mt-1 time-pill mono text-white text-lg md:text-xl">{now.time}</div>
      </div>
    </header>
  )
}

// removed fake stats component to keep UI focused on real content

function Step({ num, title, text, img, reverse }){
  return (
    <div className={`flex flex-col md:flex-row items-center gap-6 my-8 ${reverse ? 'md:flex-row-reverse' : ''}`}>
        <div className="md:flex-1 flex justify-center md:justify-start">
        {/* show original image size, with a static colorful border and consistent frame (no animation) */}
        <div className="img-border">
          <div className="rounded-2xl overflow-hidden img-frame">
            <img src={img} alt={title} className="object-contain max-w-full h-auto rounded-2xl" />
          </div>
        </div>
      </div>
      <div className="md:flex-1 text-center md:text-left">
        <div className="text-sm text-indigo-300 font-semibold">Step {num}</div>
        <div className="text-2xl md:text-3xl font-extrabold text-white mt-2">{title}</div>
        <p className="text-gray-300 mt-3 max-w-xl mx-auto md:mx-0">{text}</p>
      </div>
    </div>
  )
}

function App() {
  const [now, setNow] = useState({ date: '', time: '' })

  useEffect(() => {
    function tick(){
      const d = new Date()
      setNow({
        date: d.toLocaleDateString(),
        time: d.toLocaleTimeString()
      })
    }
    tick()
    const id = setInterval(tick, 1000)
    return () => clearInterval(id)
  }, [])

  return (
    <div className="min-h-screen bg-gradient-to-br from-[#030416] via-[#071026] to-[#061018] text-white relative overflow-hidden">
      <div className="sparkles">
        <span></span><span></span><span></span><span></span><span></span><span></span><span></span><span></span>
      </div>
      <div className="max-w-6xl mx-auto relative z-10">
        <Navbar now={now} />

        <main className="px-6 md:px-0 py-10">
          <section className="bg-transparent py-8">
            <div className="grid grid-cols-1 md:grid-cols-2 gap-8 items-center">
              <div>
                <h1 className="text-4xl md:text-5xl font-extrabold leading-tight">cli-todo — Minimal, fast, terminal-first todo</h1>
                <p className="text-gray-300 mt-4 text-lg max-w-xl">A lightweight command-line todo application written in C++ that installs system-wide, stores data in a single file, and keeps your workflow fast and keyboard driven. Includes install & uninstall scripts for easy setup.</p>

                <div className="flex flex-wrap gap-3 mt-6">
                  <a href="https://github.com/PIYUSH-GIRI23/cli-todo-app" target="_blank" rel="noreferrer" className="inline-flex items-center gap-2 px-4 py-2 bg-indigo-600 hover:bg-indigo-500 rounded-md shadow-md text-sm font-semibold">
                    Get the project (GitHub)
                  </a>
                  <a href="https://github.com/PIYUSH-GIRI23/cli-todo-app" target="_blank" rel="noreferrer" className="inline-flex items-center gap-2 px-4 py-2 border border-gray-800 rounded-md text-sm text-gray-300 hover:bg-gray-800">View on GitHub</a>
                </div>
              </div>

              <div className="flex flex-col gap-4">
                <div className="p-6 bg-[#0f0f10] rounded-2xl border border-gray-800 glass-border shadow-sm fade-in slide-up">
                  <div className="text-xs text-indigo-300 font-semibold">About</div>
                  <div className="mt-3 text-white">Install with one command, then use small, intuitive commands: add, list, delete, uninstall. Built to be minimal and fast — perfect for terminal-first workflows.</div>
                  <div className="mt-4">
                    <a href="https://github.com/PIYUSH-GIRI23/cli-todo-app" target="_blank" rel="noreferrer" className="inline-block px-4 py-2 bg-indigo-600 rounded-md text-sm font-medium shadow-sm btn-animate">View source on GitHub</a>
                  </div>
                </div>
              </div>
            </div>
          </section>

          <section className="mt-8">
            <h2 className="text-3xl font-extrabold">How it works</h2>
            <p className="text-gray-400 mt-2 max-w-2xl">Three simple steps to get started — install, use, uninstall. The following images show the scripts and common commands.</p>

            <div className="mt-6">
              <Step
                num={1}
                title="Install & Setup"
                text={"Go to main folder and run ./install.sh cmd (Make sure the file is executable)"}
                img={img1}
              />
              <Step num={2} title="Use the CLI" text="Add, list, and delete tasks from the terminal — small commands with big productivity." img={img2} reverse />
              <Step num={3} title="Uninstall" text="Run the uninstall command to remove the binary and the stored data file." img={img3} />
            </div>
          </section>

          <section className="mt-10 py-8 border-t border-gray-800">
            <div className="flex flex-col md:flex-row items-center justify-between gap-6">
              <div>
                <h3 className="text-2xl font-extrabold">Get the Project</h3>
                <p className="text-gray-400 mt-1">Open source — contributions welcome. Click through to GitHub to clone or download.</p>
              </div>

              <div className="flex gap-3 items-center">
                <a href="https://github.com/PIYUSH-GIRI23/cli-todo-app" target="_blank" rel="noreferrer" className="px-5 py-3 bg-indigo-600 rounded-lg font-semibold shadow-lg">Go to GitHub</a>
              </div>
            </div>
          </section>

          <section className="mt-10 py-8">
            <h4 className="text-xl font-bold">🌐 Connect with Me</h4>
            <div className="flex flex-wrap gap-3 mt-3 items-center">
              <a href="mailto:giri.piyush2003@gmail.com"><img src="https://img.shields.io/badge/Mail-D14836?style=for-the-badge&logo=gmail&logoColor=white" alt="Mail" /></a>
              <a href="https://github.com/PIYUSH-GIRI23"><img src="https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white" alt="GitHub" /></a>
              <a href="https://www.linkedin.com/in/piyush-giri-031b71254/"><img src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white" alt="LinkedIn" /></a>
              <a href="https://x.com/GIRIPIYUSH2310"><img src="https://img.shields.io/badge/X-000000?style=for-the-badge&logo=x&logoColor=white" alt="X" /></a>
            </div>
          </section>

          <footer className="mt-16 py-8 border-t border-gray-800 text-center text-sm text-gray-500">
            <p>© {new Date().getFullYear()} Piyush Giri. All rights reserved.</p>
            <p className="mt-2 text-indigo-400">
              For more projects, visit{' '}
              <a href="https://piyx.me" target="_blank" rel="noreferrer" className="hover:text-indigo-300 underline underline-offset-4 transition-colors font-medium">
                piyx.me
              </a>
            </p>
          </footer>
        </main>
      </div>
    </div>
  )
}

export default App
