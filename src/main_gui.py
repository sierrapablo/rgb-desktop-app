import tkinter as tk
from tkinter import ttk
from src.color_picker import ColorPickerApp


class MainGUI:

    def __init__(self, root):
        self.root = root
        self.root.title("LED Controller")
        self.root.geometry("400x300")

        # Crear el Notebook (pestañas)
        self.notebook = ttk.Notebook(self.root)
        self.notebook.pack(pady=10, expand=True)

        # Crear los marcos para cada pestaña
        self.tab1 = ttk.Frame(self.notebook)
        self.tab2 = ttk.Frame(self.notebook)
        self.tab3 = ttk.Frame(self.notebook)

        # Añadir pestañas al Notebook
        self.notebook.add(self.tab1, text="Panel Frontal")
        self.notebook.add(self.tab2, text="Ventiladores Traseros y Superiores")
        self.notebook.add(self.tab3, text="Fondo")

        # Añadir widgets a la primera pestaña
        self.create_color_section(self.tab1)

        # Añadir widgets a la segunda pestaña
        self.create_color_section(self.tab2)

        # Añadir widgets a la tercera pestaña
        self.create_color_section(self.tab3)

        # Botón aplicar debajo de las pestañas
        self.apply_button = tk.Button(self.root, text="Aplicar")
        self.apply_button.pack(pady=10)

    def create_color_section(self, parent):
        """Create a section with a color picker button and a color display."""
        frame = tk.Frame(parent)
        frame.pack(pady=10, padx=10, fill=tk.X)

        # Label for color section
        color_label = tk.Label(frame, text="Color")
        color_label.pack(side=tk.LEFT, padx=5)

        # Button to open color picker
        color_button = tk.Button(
            frame, text="Seleccionar Color", command=self.open_color_picker
        )
        color_button.pack(side=tk.LEFT, padx=5)

        # Label to show the current color
        self.color_display = tk.Label(
            frame,
            text="Color Actual", bg="#ffffff",
            width=20, height=2, relief=tk.SUNKEN
        )
        self.color_display.pack(side=tk.LEFT, padx=5, expand=True, fill=tk.X)

    def open_color_picker(self):
        """Function to open the color picker dialog."""
        # Create a Toplevel window which will be hidden but serves as a parent
        # for the color picker
        temp_window = tk.Toplevel(self.root)
        temp_window.withdraw()  # Hide the Toplevel window

        # Call ColorPickerApp and update the color display on selection
        ColorPickerApp(
            master=temp_window, on_color_selected=self.update_color_display
        )

    def update_color_display(self, color):
        """Update the color display label with the selected color."""
        self.color_display.config(bg=color)
