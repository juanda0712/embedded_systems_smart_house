async function obtenerLuces() {
    const res = await fetch('/api/luces');
    return await res.json();
}

async function actualizarLuces(nuevoEstado) {
    await fetch('/api/luces', {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({ luces: nuevoEstado })
    });
}

async function cambiarLuz(index) {
    const luces = await obtenerLuces();
    luces[index] = !luces[index];
    await actualizarLuces(luces);
    renderLuces();
    actualizarCasa();
}

async function renderLuces() {
    const luces = await obtenerLuces();
    const cont = document.getElementById('controles-luces');
    cont.innerHTML = '<h2>Control de luces</h2>';

    luces.forEach((estado, i) => {
        const btn = document.createElement('button');
        btn.textContent = `Luz ${i + 1}: ${estado ? 'Encendida' : 'Apagada'}`;
        btn.onclick = () => cambiarLuz(i);
        cont.appendChild(btn);
    });
}

async function renderPuertas() {
    const res = await fetch('/api/puertas');
    const puertas = await res.json();
    const cont = document.getElementById('estado-puertas');
    cont.innerHTML = '<h2>Estado de puertas</h2>';

    puertas.forEach((estado, i) => {
        const p = document.createElement('p');
        p.textContent = `Puerta ${i + 1}: ${estado ? 'Abierta' : 'Cerrada'}`;
        cont.appendChild(p);
    });
}

async function actualizarCasa() {
    const luces = await obtenerLuces();
    for (let i = 0; i < luces.length; i++) {
        const hab = document.getElementById(`habitacion-${i + 1}`);
        if (hab) {
            hab.setAttribute('fill', luces[i] ? '#ffff66' : '#ddd');
        }
    }
}


function verJardin() {
    const cont = document.getElementById('foto-jardin');
    const img = document.createElement('img');
    img.src = '/api/camara?' + new Date().getTime(); // evitar caché
    img.alt = "Foto del jardín";
    img.style.maxWidth = '100%';
    cont.innerHTML = '';
    cont.appendChild(img);
}

function init() {
    renderLuces();
    renderPuertas();
    actualizarCasa();

    setInterval(renderPuertas, 2000);
    setInterval(actualizarCasa, 2000);
}

window.onload = init;
