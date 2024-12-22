import tkinter as tk
from tkinter import ttk, messagebox

# Train Class
class Train:
    def __init__(self, train_id, name, route, total_seats):
        self.train_id = train_id
        self.name = name
        self.route = route
        self.total_seats = total_seats
        self.booked_seats = 0

    def book_seat(self):
        if self.booked_seats < self.total_seats:
            self.booked_seats += 1
            return True
        return False

    def cancel_seat(self):
        if self.booked_seats > 0:
            self.booked_seats -= 1
            return True
        return False

    def available_seats(self):
        return self.total_seats - self.booked_seats

    def __str__(self):
        return f"Train ID: {self.train_id}, Name: {self.name}, Route: {self.route}, Available Seats: {self.available_seats()}"

# Railway Management System with Custom Tkinter
class RailwayManagementSystem:
    def __init__(self, root):
        self.root = root
        self.root.title("Railway Management System")
        self.root.geometry("900x600")
        self.root.configure(bg="#2E2E2E")

        # Custom styles for dark theme
        self.style = ttk.Style()
        self.style.configure("TLabel", font=("Helvetica", 12), foreground="white", background="#2E2E2E")
        self.style.configure("TButton", font=("Helvetica", 12), padding=5, background="#FF6F61", foreground="white")
        self.style.map("TButton", background=[("active", "#FF6F61")])

        self.style.configure("Title.TLabel", font=("Helvetica", 18, "bold"), foreground="#FF6F61", background="#2E2E2E")

        # Data
        self.trains = [
            Train(101, "Express 1", "Samannod - Cairo", 200),
            Train(102, "Express 2", "Alexandria - Mansoura", 250),
            Train(103, "Express 3", "Aswan - Cairo", 100),
        ]
        self.users = {"admin": "admin123"}
        self.passenger_tickets = {}
        self.current_user = None

        # Display main menu
        self.main_menu()

    def clear_screen(self):
        for widget in self.root.winfo_children():
            widget.destroy()

    def main_menu(self):
        self.clear_screen()

        ttk.Label(self.root, text="Railway Management System", style="Title.TLabel").pack(pady=20)

        ttk.Button(self.root, text="Admin Login", command=self.admin_login).pack(pady=10)
        ttk.Button(self.root, text="Passenger Login", command=self.passenger_login).pack(pady=10)
        ttk.Button(self.root, text="Register as Passenger", command=self.register_passenger).pack(pady=10)
        ttk.Button(self.root, text="Exit", command=self.root.quit).pack(pady=10)

    def admin_login(self):
        self.clear_screen()

        ttk.Label(self.root, text="Admin Login", style="Title.TLabel").pack(pady=20)

        ttk.Label(self.root, text="Username:").pack()
        username_entry = ttk.Entry(self.root)
        username_entry.pack()

        ttk.Label(self.root, text="Password:").pack()
        password_entry = ttk.Entry(self.root, show="*")
        password_entry.pack()

        def login():
            username = username_entry.get()
            password = password_entry.get()

            if username == "admin" and password == "admin123":
                self.admin_menu()
            else:
                messagebox.showerror("Login Failed", "Invalid admin credentials!")

        ttk.Button(self.root, text="Login", command=login).pack(pady=10)
        ttk.Button(self.root, text="Back", command=self.main_menu).pack(pady=10)

    def admin_menu(self):
        self.clear_screen()

        ttk.Label(self.root, text="Admin Menu", style="Title.TLabel").pack(pady=20)

        ttk.Button(self.root, text="Add Train", command=self.add_train).pack(pady=10)
        ttk.Button(self.root, text="View All Trains", command=self.view_trains).pack(pady=10)
        ttk.Button(self.root, text="Back", command=self.main_menu).pack(pady=10)

    def add_train(self):
        self.clear_screen()

        ttk.Label(self.root, text="Add Train", style="Title.TLabel").pack(pady=20)

        ttk.Label(self.root, text="Train ID:").pack()
        train_id_entry = ttk.Entry(self.root)
        train_id_entry.pack()

        ttk.Label(self.root, text="Train Name:").pack()
        train_name_entry = ttk.Entry(self.root)
        train_name_entry.pack()

        ttk.Label(self.root, text="Route:").pack()
        route_entry = ttk.Entry(self.root)
        route_entry.pack()

        ttk.Label(self.root, text="Total Seats:").pack()
        total_seats_entry = ttk.Entry(self.root)
        total_seats_entry.pack()

        def save_train():
            try:
                train_id = int(train_id_entry.get())
                name = train_name_entry.get()
                route = route_entry.get()
                total_seats = int(total_seats_entry.get())

                self.trains.append(Train(train_id, name, route, total_seats))
                messagebox.showinfo("Success", "Train added successfully!")
                self.admin_menu()
            except ValueError:
                messagebox.showerror("Error", "Invalid input. Please check your entries.")

        ttk.Button(self.root, text="Add Train", command=save_train).pack(pady=10)
        ttk.Button(self.root, text="Back", command=self.admin_menu).pack(pady=10)

    def view_trains(self):
        self.clear_screen()

        ttk.Label(self.root, text="Available Trains", style="Title.TLabel").pack(pady=20)

        for train in self.trains:
            ttk.Label(self.root, text=str(train)).pack(pady=5)

        ttk.Button(self.root, text="Back", command=self.admin_menu).pack(pady=20)

    def view_trains_passenger(self, username):
        self.clear_screen()

        ttk.Label(self.root, text="Available Trains", style="Title.TLabel").pack(pady=20)

        for train in self.trains:
            ttk.Label(self.root, text=str(train)).pack(pady=5)

        ttk.Button(self.root, text="Back", command=lambda: self.passenger_menu(username)).pack(pady=20)

    def passenger_login(self):
        self.clear_screen()

        ttk.Label(self.root, text="Passenger Login", style="Title.TLabel").pack(pady=20)

        ttk.Label(self.root, text="Username:").pack()
        username_entry = ttk.Entry(self.root)
        username_entry.pack()

        ttk.Label(self.root, text="Password:").pack()
        password_entry = ttk.Entry(self.root, show="*")
        password_entry.pack()

        def login():
            username = username_entry.get()
            password = password_entry.get()

            if username in self.users and self.users[username] == password:
                self.passenger_menu(username)
            else:
                messagebox.showerror("Login Failed", "Invalid credentials!")

        ttk.Button(self.root, text="Login", command=login).pack(pady=10)
        ttk.Button(self.root, text="Back", command=self.main_menu).pack(pady=10)

    def register_passenger(self):
        self.clear_screen()

        ttk.Label(self.root, text="Register as Passenger", style="Title.TLabel").pack(pady=20)

        ttk.Label(self.root, text="Username:").pack()
        username_entry = ttk.Entry(self.root)
        username_entry.pack()

        ttk.Label(self.root, text="Password:").pack()
        password_entry = ttk.Entry(self.root, show="*")
        password_entry.pack()

        def register():
            username = username_entry.get()
            password = password_entry.get()

            if not username or not password:
                messagebox.showerror("Error", "All fields are required!")
                return

            if username in self.users:
                messagebox.showerror("Error", "Username already exists!")
                return

            self.users[username] = password
            messagebox.showinfo("Success", "Registration successful! You can now log in.")
            self.main_menu()

        ttk.Button(self.root, text="Register", command=register).pack(pady=10)
        ttk.Button(self.root, text="Back", command=self.main_menu).pack(pady=10)

    def passenger_menu(self, username):
        self.clear_screen()
        ttk.Label(self.root, text=f"Welcome, {username}", style="Title.TLabel").pack(pady=20)

        ttk.Label(self.root, text="Available Trains", style="Title.TLabel").pack(pady=20)

        for train in self.trains:
            ttk.Label(self.root, text=str(train)).pack(pady=5)
        ttk.Button(self.root, text="Book Ticket", command=lambda: self.book_ticket(username)).pack(pady=10)
        ttk.Button(self.root, text="Cancel Ticket", command=lambda: self.cancel_ticket(username)).pack(pady=10)
        ttk.Button(self.root, text="View Booked Tickets", command=lambda: self.view_booked_tickets(username)).pack(pady=10)
        ttk.Button(self.root, text="Back", command=self.main_menu).pack(pady=10)

    def book_ticket(self, username):
        self.clear_screen()

        ttk.Label(self.root, text="Book Ticket", style="Title.TLabel").pack(pady=20)

        ttk.Label(self.root, text="Train ID:").pack()
        train_id_entry = ttk.Entry(self.root)
        train_id_entry.pack()

        def confirm_booking():
            train_id = int(train_id_entry.get())

            train = next((t for t in self.trains if t.train_id == train_id), None)
            if train and train.book_seat():
                self.passenger_tickets.setdefault(username, []).append(train_id)
                messagebox.showinfo("Success", "Ticket booked successfully!")
            else:
                messagebox.showerror("Error", "Failed to book the ticket. Please try again.")

            self.passenger_menu(username)

        ttk.Button(self.root, text="Book Ticket", command=confirm_booking).pack(pady=10)
        ttk.Button(self.root, text="Back", command=lambda: self.passenger_menu(username)).pack(pady=10)

    def cancel_ticket(self, username):
        self.clear_screen()

        ttk.Label(self.root, text="Cancel Ticket", style="Title.TLabel").pack(pady=20)

        ttk.Label(self.root, text="Train ID:").pack()
        train_id_entry = ttk.Entry(self.root)
        train_id_entry.pack()

        def confirm_cancellation():
            train_id = int(train_id_entry.get())

            if train_id in self.passenger_tickets.get(username, []):
                self.passenger_tickets[username].remove(train_id)
                train = next((t for t in self.trains if t.train_id == train_id), None)
                if train:
                    train.cancel_seat()
                messagebox.showinfo("Success", "Ticket cancelled successfully.")
            else:
                messagebox.showerror("Error", "You have not booked a ticket for this train.")

            self.passenger_menu(username)

        ttk.Button(self.root, text="Cancel Ticket", command=confirm_cancellation).pack(pady=10)
        ttk.Button(self.root, text="Back", command=lambda: self.passenger_menu(username)).pack(pady=10)

    def view_booked_tickets(self, username):
        self.clear_screen()

        ttk.Label(self.root, text="Booked Tickets", style="Title.TLabel").pack(pady=20)

        booked_trains = self.passenger_tickets.get(username, [])
        if not booked_trains:
            ttk.Label(self.root, text="No booked tickets.").pack(pady=10)
        else:
            for train_id in booked_trains:
                train = next((t for t in self.trains if t.train_id == train_id), None)
                if train:
                    ttk.Label(self.root, text=str(train)).pack(pady=5)

        ttk.Button(self.root, text="Back", command=lambda: self.passenger_menu(username)).pack(pady=20)

# Run the application
if __name__ == "__main__":
    root = tk.Tk()
    app = RailwayManagementSystem(root)
    root.mainloop()
