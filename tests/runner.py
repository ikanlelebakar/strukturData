import subprocess
import threading
import queue
import time
import re
import sys

def strip_ansi(text):
    """Removes ANSI escape codes (e.g., clear screen, color codes) from string."""
    ansi_escape = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')
    return ansi_escape.sub('', text)

class CLIAppRunner:
    def __init__(self, binary_path="./sistem_turnamen", verbose=True, delay=0.4, interactive=None):
        self.verbose = verbose
        self.delay = delay
        import os
        self.interactive = interactive if interactive is not None else (os.environ.get("INTERACTIVE") == "1")
        self.proc = subprocess.Popen(
            [binary_path],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            bufsize=0
        )
        self.stdout_queue = queue.Queue()
        self.stderr_queue = queue.Queue()
        
        self.stdout_thread = threading.Thread(target=self._enqueue_output, args=(self.proc.stdout, self.stdout_queue), daemon=True)
        self.stderr_thread = threading.Thread(target=self._enqueue_output, args=(self.proc.stderr, self.stderr_queue), daemon=True)
        
        self.stdout_thread.start()
        self.stderr_thread.start()
        
        self.log = []

    def _enqueue_output(self, out, q):
        while True:
            try:
                char = out.read(1)
                if not char:
                    break
                if self.verbose:
                    sys.stdout.write(char)
                    sys.stdout.flush()
                q.put(char)
            except Exception:
                break

    def read_until(self, expected_suffixes, timeout=3.0):
        """Reads stdout until one of the expected suffixes is at the end of the accumulated buffer (stripped of ANSI escapes), or timeout is reached."""
        if isinstance(expected_suffixes, str):
            expected_suffixes = [expected_suffixes]
            
        accumulated_raw = ""
        start_time = time.time()
        
        while time.time() - start_time < timeout:
            try:
                char = self.stdout_queue.get_nowait()
                accumulated_raw += char
                stripped = strip_ansi(accumulated_raw)
                for suffix in expected_suffixes:
                    if stripped.endswith(suffix):
                        self.log.append(f"READ: {stripped}")
                        return stripped
            except queue.Empty:
                time.sleep(0.005)
                
        stripped_final = strip_ansi(accumulated_raw)
        self.log.append(f"READ_TIMEOUT (Buffer: {stripped_final})")
        return stripped_final

    def write(self, data):
        self.log.append(f"WRITE: {data}")
        if self.verbose:
            sys.stdout.write(data)
            sys.stdout.flush()
        self.proc.stdin.write(data)
        self.proc.stdin.flush()

    def write_line(self, line):
        if self.interactive:
            print(f"\n\033[33m[TEST: Press ENTER to send '{line}']\033[0m", end="", flush=True)
            input()
        elif self.delay > 0:
            time.sleep(self.delay)
        self.write(line + "\n")

    def close(self):
        if self.proc.poll() is None:
            self.proc.terminate()
            try:
                self.proc.wait(timeout=1.0)
            except subprocess.TimeoutExpired:
                self.proc.kill()
        if self.proc.stdout:
            self.proc.stdout.close()
        if self.proc.stderr:
            self.proc.stderr.close()
        if self.proc.stdin:
            self.proc.stdin.close()
        self.log.append("PROCESS CLOSED")

    def get_full_log(self):
        return "\n".join(self.log)
