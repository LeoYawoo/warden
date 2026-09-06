"""Shared pytest configuration for warden tests."""

import os

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DATA_DIR = os.path.join(PROJECT_ROOT, "data")
FFMPEG_PATH = os.path.join(DATA_DIR, "tools", "ffmpeg", "ffmpeg.exe")


def pytest_configure(config):
    """Register custom markers."""
    config.addinivalue_line("markers", "blp: BLP decode quality tests")
