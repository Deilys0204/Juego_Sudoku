document.addEventListener('DOMContentLoaded', () => {
    const urlParams = new URLSearchParams(window.location.search);
    const dificultad = urlParams.get('dificultad') || 'facil';
    const tituloDificultad = document.getElementById('titulo-dificultad');
    tituloDificultad.textContent = dificultad.charAt(0).toUpperCase() + dificultad.slice(1);

    fetch(`/cgi-bin/generar_tablero_${dificultad}.cgi`)
        .then(response => response.text())
        .then(data => {
            document.getElementById('sudoku-tablero').innerHTML = data;
        })
        .catch(error => console.error('Error cargando el tablero:', error));

    iniciarTemporizador();

    document.getElementById('completado-btn').addEventListener('click', validarSudoku);
});

function iniciarTemporizador() {
    let timerElement = document.getElementById('timer');
    let minutes = 0;
    let seconds = 0;

    setInterval(() => {
        seconds++;
        if (seconds === 60) {
            minutes++;
            seconds = 0;
        }
        timerElement.textContent = `${String(minutes).padStart(2, '0')}:${String(seconds).padStart(2, '0')}`;
    }, 1000);
}

function validarSudoku() {
    const cells = document.querySelectorAll('#sudoku-tablero input');
    let completo = true;

    cells.forEach(cell => {
        if (cell.value === '' || isNaN(cell.value) || cell.value < 1 || cell.value > 9) {
            completo = false;
        }
    });

    if (completo) {
        alert('¡Sudoku completado correctamente!');
    } else {
        alert('El Sudoku no está completo o contiene errores.');
    }
}