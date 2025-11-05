""" Shared utilities for VectorNav SDK Python examples.

This module contains common utility functions used across multiple examples
to eliminate code duplication.

MIT License
Copyright (c)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
"""

from pathlib import Path
import platform
import re

try:
    import serial.tools.list_ports  # type: ignore[import-untyped]
except ImportError:
    serial = None


def get_default_port() -> str:
    """Get the default serial port based on platform and available devices.

    This function attempts to find the most appropriate serial port for
    VectorNav devices by checking for FTDI USB-RS422 cables on all platforms,
    falling back to platform-specific defaults.

    Returns:
        str: Default serial port path for the current platform.
             - Windows with FTDI: First available FTDI USB-RS422 cable
             - Windows fallback: First available COM port or "COM1"
             - Unix with FTDI device: First available FTDI USB-RS422 cable
             - Unix fallback: "/dev/ttyUSB0"
             - macOS fallback: "/dev/tty.usbserial-*" or "/dev/ttyUSB0"
    """
    system = platform.system()

    if system == "Windows":
        # Try to find FTDI device first
        ftdi_port = _find_ftdi_com_port()
        if ftdi_port:
            return ftdi_port

        # Fallback to any available COM port
        com_ports = _get_windows_com_ports()
        if com_ports:
            return com_ports[0]  # Return the lowest numbered COM port

        # Final fallback
        return "COM1"

    # For Unix-like systems (Linux, macOS), try to find FTDI devices
    try:
        ftdi_path = Path("/dev/serial/by-id")
        if ftdi_path.exists():
            ftdi_devices = list(ftdi_path.glob("usb-FTDI_USB-RS422_Cable_FT*"))
            if ftdi_devices:
                return str(ftdi_devices[0])  # Use the first FTDI device found
    except (OSError, PermissionError):
        pass

    # macOS-specific fallback
    if system == "Darwin":
        try:
            dev_path = Path("/dev")
            # Look for common macOS USB serial devices
            macos_devices = list(dev_path.glob("tty.usbserial-*"))
            if macos_devices:
                return str(macos_devices[0])
        except (OSError, PermissionError):
            pass

    # Final fallback for all Unix-like systems
    return "/dev/ttyUSB0"


def _find_ftdi_com_port() -> str | None:
    """Find FTDI USB-RS422 device on Windows.

    Returns:
        COM port name if FTDI device found, None otherwise.
    """
    if serial is None:
        return None

    for port in serial.tools.list_ports.comports():
        if port.vid == 0x0403:  # FTDI Vendor ID
            return port.device

    return None


def _get_windows_com_ports() -> list[str]:
    """Get available COM ports on Windows using pyserial.

    Returns:
        List of available COM port names, sorted by port number.
    """
    if serial is None:
        return []

    ports = [port.device for port in serial.tools.list_ports.comports()]

    # Sort COM ports numerically (COM1, COM2, COM10, etc.)
    def com_port_key(port: str) -> int:
        match = re.search(r"COM(\d+)", port)
        return int(match.group(1)) if match else 999

    return sorted(ports, key=com_port_key)
