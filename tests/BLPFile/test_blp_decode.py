"""BLP decode quality test - compare blp2tga output with reference tool using PSNR/SSIM."""

import subprocess
import os
import pytest

FFMPEG = os.path.join(os.path.dirname(__file__), "..", "..", "data", "tools", "ffmpeg", "ffmpeg.exe")
DATA_DIR = os.path.join(os.path.dirname(__file__), "..", "..", "data", "blp")

# Minimum PSNR thresholds (dB)
PSNR_MIN_R = 40.0
PSNR_MIN_G = 40.0
PSNR_MIN_B = 10.0  # BLP1 B channel may differ from reference tool

# Minimum SSIM thresholds
SSIM_MIN_R = 0.9
SSIM_MIN_G = 0.9


def run_ffmpeg_psnr(img1: str, img2: str) -> dict:
    """Run ffmpeg PSNR filter and return per-channel values."""
    cmd = [
        FFMPEG, "-i", img1, "-i", img2,
        "-filter_complex", "psnr=stats_file=-",
        "-f", "null", "-"
    ]
    result = subprocess.run(cmd, capture_output=True, text=True)
    for line in result.stderr.splitlines():
        if "PSNR" in line and "r:" in line:
            vals = {}
            for part in line.split():
                if ":" in part and part[0] in "rgba":
                    ch, val = part.split(":")
                    vals[ch] = float(val)
                elif part.startswith("average:"):
                    vals["average"] = float(part.split(":")[1])
            return vals
    raise RuntimeError(f"Could not parse PSNR from ffmpeg output:\n{result.stderr}")


def run_ffmpeg_ssim(img1: str, img2: str) -> dict:
    """Run ffmpeg SSIM filter and return per-channel values."""
    cmd = [
        FFMPEG, "-i", img1, "-i", img2,
        "-filter_complex", "ssim",
        "-f", "null", "-"
    ]
    result = subprocess.run(cmd, capture_output=True, text=True)
    for line in result.stderr.splitlines():
        if "SSIM" in line and "R:" in line:
            vals = {}
            for part in line.replace(",", "").split():
                if ":" in part and part[0] in "RGA":
                    ch, val = part.split(":")
                    vals[ch] = float(val)
                elif part.startswith("All:"):
                    vals["All"] = float(part.split(":")[1])
            return vals
    raise RuntimeError(f"Could not parse SSIM from ffmpeg output:\n{result.stderr}")


# (blp_file, reference_tga, description)
BLP_TEST_CASES = [
    ("HeroArchmage.blp", "HeroArchmage.tool.tga", "HeroArchmage - hero unit texture"),
]


@pytest.mark.blp
@pytest.mark.parametrize("blp_file,ref_tga,desc", BLP_TEST_CASES, ids=[c[0] for c in BLP_TEST_CASES])
class TestBLPDecode:
    """BLP decode quality tests."""

    def test_psnr(self, blp_file: str, ref_tga: str, desc: str):
        """PSNR per-channel comparison against reference tool."""
        our_tga = os.path.join(DATA_DIR, blp_file.replace(".blp", ".tga"))
        ref_path = os.path.join(DATA_DIR, ref_tga)

        if not os.path.exists(our_tga):
            pytest.skip(f"Output not found: {our_tga}")
        if not os.path.exists(ref_path):
            pytest.skip(f"Reference not found: {ref_path}")

        psnr = run_ffmpeg_psnr(our_tga, ref_path)

        # Attach to report
        report_data = (
            f"| Channel | PSNR (dB) | Threshold |\n"
            f"|---------|-----------|-----------|\n"
            f"| R       | {psnr.get('r', 0):.2f}     | {PSNR_MIN_R}     |\n"
            f"| G       | {psnr.get('g', 0):.2f}     | {PSNR_MIN_G}     |\n"
            f"| B       | {psnr.get('b', 0):.2f}     | {PSNR_MIN_B}     |\n"
            f"| Average | {psnr.get('average', 0):.2f}     | -       |\n"
        )
        self._report = report_data

        assert psnr.get("r", 0) >= PSNR_MIN_R, f"Red PSNR {psnr.get('r', 0):.2f} dB < {PSNR_MIN_R}"
        assert psnr.get("g", 0) >= PSNR_MIN_G, f"Green PSNR {psnr.get('g', 0):.2f} dB < {PSNR_MIN_G}"
        assert psnr.get("b", 0) >= PSNR_MIN_B, f"Blue PSNR {psnr.get('b', 0):.2f} dB < {PSNR_MIN_B}"

    def test_ssim(self, blp_file: str, ref_tga: str, desc: str):
        """SSIM per-channel comparison against reference tool."""
        our_tga = os.path.join(DATA_DIR, blp_file.replace(".blp", ".tga"))
        ref_path = os.path.join(DATA_DIR, ref_tga)

        if not os.path.exists(our_tga):
            pytest.skip(f"Output not found: {our_tga}")
        if not os.path.exists(ref_path):
            pytest.skip(f"Reference not found: {ref_path}")

        ssim = run_ffmpeg_ssim(our_tga, ref_path)

        report_data = (
            f"| Channel | SSIM    | Threshold |\n"
            f"|---------|---------|-----------|\n"
            f"| R       | {ssim.get('R', 0):.4f} | {SSIM_MIN_R}     |\n"
            f"| G       | {ssim.get('G', 0):.4f} | {SSIM_MIN_G}     |\n"
            f"| All     | {ssim.get('All', 0):.4f} | -         |\n"
        )
        self._report = report_data

        assert ssim.get("R", 0) >= SSIM_MIN_R, f"Red SSIM {ssim.get('R', 0):.4f} < {SSIM_MIN_R}"
        assert ssim.get("G", 0) >= SSIM_MIN_G, f"Green SSIM {ssim.get('G', 0):.4f} < {SSIM_MIN_G}"
