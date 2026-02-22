import unittest
from unittest.mock import MagicMock, patch

import iterfzf

flavors = [
    "Chocolate",
    "Chocolate Chip",
    "Vanilla",
    "Strawberry",
    "Blueberry",
    "Rocky Road",
]


class IterFzfTest(unittest.TestCase):

    def test_no_query(self):
        choice = iterfzf.iterfzf(flavors, executable="fzf")
        self.assertEqual("Chocolate", choice)

    def test_supports_color_kwarg(self):
        choice = iterfzf.iterfzf(
            flavors,
            executable="fzf",
            color={
                "fg": "#d0d0d0",
                "bg": "#121212",
                "hl": "#5f87af",
                "fg+": "#d0d0d0",
                "bg+": "#262626",
                "hl+": "#5fd7ff",
                "info": "#afaf87",
                "prompt": "#d7005f",
                "pointer": "#af5fff",
                "marker": "#87ff00",
                "spinner": "#af5fff",
                "header": "#87afaf",
            },
        )
        self.assertEqual("Chocolate", choice)

    def test_select_one(self):
        choice = iterfzf.iterfzf(
            flavors, query="Vani", __extra__=["-1"], executable="fzf"
        )
        self.assertEqual("Vanilla", choice)

    def test_support_header_kwarg(self):
        choice = iterfzf.iterfzf(
            flavors,
            query="Vani",
            __extra__=["-1"],
            executable="fzf",
            header="The header should not cause errors",
        )
        self.assertEqual("Vanilla", choice)

    def test_select_one_ambiguous(self):
        choice = iterfzf.iterfzf(
            flavors, query="Choc", __extra__=["-1"], executable="fzf"
        )
        self.assertTrue(choice.rfind("Chocolate") == 0)

    @patch("subprocess.Popen")
    def test_raises_keyboard_interrupt(self, mock_open):
        mock_process = MagicMock()
        mock_open.return_value = mock_process

        mock_process.wait.return_value = iterfzf.INTERRUPT_EXIT_CODE

        self.assertRaises(
            KeyboardInterrupt,
            lambda: iterfzf.iterfzf(flavors, executable="fzf"),
        )

    def test_support_tmux_bool(self):
        choice = iterfzf.iterfzf(
            flavors,
            query="Vani",
            __extra__=["-1"],
            executable="fzf",
            tmux=True,
        )
        self.assertEqual("Vanilla", choice)

    def test_support_tmux_str(self):
        choice = iterfzf.iterfzf(
            flavors,
            query="Vani",
            __extra__=["-1"],
            executable="fzf",
            tmux="top,60%",
        )
        self.assertEqual("Vanilla", choice)

    @patch("subprocess.Popen")
    def test_read0_passes_flags(self, mock_popen):
        mock_process = MagicMock()
        mock_popen.return_value = mock_process
        mock_process.wait.return_value = 0
        mock_process.stdout.read.return_value = b"Chocolate\0"

        iterfzf.iterfzf(flavors, executable="fzf", read0=True)

        cmd = mock_popen.call_args[0][0]
        self.assertIn("--read0", cmd)
        self.assertIn("--print0", cmd)

    @patch("subprocess.Popen")
    def test_read0_allows_newlines(self, mock_popen):
        mock_process = MagicMock()
        mock_popen.return_value = mock_process
        mock_process.wait.return_value = 0
        mock_process.stdout.read.return_value = b"Line1\nLine2\0"

        items_with_newlines = ["Line1\nLine2", "Line3\nLine4"]
        result = iterfzf.iterfzf(
            items_with_newlines, executable="fzf", read0=True
        )

        self.assertEqual("Line1\nLine2", result)

    def test_read0_rejects_nul(self):
        items_with_nul = ["Item\0WithNul", "Normal"]
        with self.assertRaises(ValueError) as ctx:
            iterfzf.iterfzf(items_with_nul, executable="fzf", read0=True)
        self.assertIn("NUL", str(ctx.exception))

    @patch("subprocess.Popen")
    def test_read0_stdin_uses_nul_separator(self, mock_popen):
        mock_process = MagicMock()
        mock_popen.return_value = mock_process
        mock_process.wait.return_value = 0
        mock_process.stdout.read.return_value = b"Chocolate\0"

        iterfzf.iterfzf(flavors[:2], executable="fzf", read0=True)

        writes = mock_process.stdin.write.call_args_list
        self.assertEqual(writes[0][0][0], b"Chocolate\0")
        self.assertEqual(writes[1][0][0], b"Chocolate Chip\0")

    @patch("subprocess.Popen")
    def test_read0_parses_nul_output(self, mock_popen):
        mock_process = MagicMock()
        mock_popen.return_value = mock_process
        mock_process.wait.return_value = 0
        mock_process.stdout.read.return_value = b"Item1\0Item2\0Item3\0"

        result = iterfzf.iterfzf(
            flavors, executable="fzf", read0=True, multi=True
        )

        self.assertEqual(["Item1", "Item2", "Item3"], result)

    @patch("subprocess.Popen")
    def test_read0_with_print_query(self, mock_popen):
        mock_process = MagicMock()
        mock_popen.return_value = mock_process
        mock_process.wait.return_value = 0
        mock_process.stdout.read.return_value = b"query\0Selected\0"

        query, result = iterfzf.iterfzf(
            flavors, executable="fzf", read0=True, print_query=True
        )

        self.assertEqual("query", query)
        self.assertEqual("Selected", result)
