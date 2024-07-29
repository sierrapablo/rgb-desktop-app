import tkinter as tk
from tkinter import colorchooser


class ColorPickerApp:

    def __init__(self, master=None, on_color_selected=None):
        """Initialize the color picker application."""
        self.master = master
        self.master.title("Color Picker")
        self.on_color_selected = on_color_selected  # Callback function

        # Define variables
        self.red = tk.IntVar()
        self.green = tk.IntVar()
        self.blue = tk.IntVar()
        self.hex_value = tk.StringVar()

        # Open the color chooser dialog
        self.open_color_picker()

    def open_color_picker(self):
        """Open the standard color chooser and handle the selection."""
        color_code = colorchooser.askcolor(
            title="Choose color", parent=self.master
        )
        if color_code[1]:  # Check if the user didn't cancel the color chooser
            color = color_code[1]
            r, g, b = map(int, color_code[0])
            self.red.set(r)
            self.green.set(g)
            self.blue.set(b)
            self.hex_value.set(color)
            self.update_color_preview()
            if self.on_color_selected:
                # Call the callback with selected color
                self.on_color_selected(color)
        else:
            # If the user cancels, set default values or handle as needed
            self.red.set(0)
            self.green.set(0)
            self.blue.set(0)
            self.hex_value.set('#000000')
            self.update_color_preview()
            if self.on_color_selected:
                self.on_color_selected('#000000')  # Default color on cancel

        # Close the application window
        self.master.destroy()

    def update_color_preview(self):
        """Update the color preview based on RGB values."""
        try:
            r, g, b = self.red.get(), self.green.get(), self.blue.get()
            color = f'#{r:02x}{g:02x}{b:02x}'
            self.hex_value.set(color)
        except tk.TclError:
            pass
