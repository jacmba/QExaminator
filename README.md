# QExaminator

QExaminator is a Qt-based desktop application designed for practicing multiple-choice tests. It allows users to load question sets from a JSON file, answer questions interactively, and receive feedback on their performance.

## Features

- Load and display multiple-choice questions from a JSON file
- Support for both single-answer and multiple-answer questions
- Randomized question selection
- User-friendly interface with Qt Widgets
- Feedback highlighting correct and incorrect answers
- Timer support for timed quizzes

## Installation

### Prerequisites

- Qt 5 or Qt 6 (including Qt Creator for easier development)
- C++ compiler supporting C++17 or later

### Build & Run

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/qexaminator.git
   cd qexaminator
   ```
2. Open the project in Qt Creator or build manually using qmake:
   ```sh
   qmake
   make
   ```
3. Run the application:
   ```sh
   ./QExaminator
   ```

## Usage

1. Load a set of questions from a JSON file.
2. Select a category (if applicable).
3. Start answering the questions.
4. Submit answers and receive immediate feedback.
5. Continue until all questions are answered.

## Question Data Format

QExaminator expects questions to be provided in a JSON file. The format follows this structure:

```json
[
    {
        "id": 1,
        "category": "General Knowledge",
        "question": "What is the capital of France?",
        "answers": ["Paris", "Berlin", "Madrid"],
        "right_answers": [0]
    },
    {
        "id": 2,
        "category": "Science",
        "question": "What is the chemical symbol for water?",
        "answers": ["H2O", "O2", "CO2"],
        "right_answers": [0]
    }
]
```
- `id`: Unique identifier for the question
- `category`: The topic category
- `question`: The question text
- `answers`: An array of possible answers
- `right_answers`: An array of indices indicating the correct answer(s)

## Customization

### Changing the Application Icon
If the application icon does not display correctly on Linux, try setting it manually using `XDG_ICON_RESOURCE`:
```sh
xdg-icon-resource install --size 64 path/to/icon.png qexaminator
```

### Styling
The application uses QSS (Qt Style Sheets) for styling. You can customize the appearance by modifying the included QSS file.

## Contributing
Feel free to submit pull requests or report issues. Contributions are always welcome!

## License
This project is licensed under the MIT License. See the LICENSE file for details.

