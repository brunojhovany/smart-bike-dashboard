// request to server /dbdata for load current data to form, using axios

axios.get('/dbdata').then((response) => {
    /* {"odometer":27630,"next_service":30000,"oil_service":30000, "oil_alert": true, "service_alert":true} */
    let data = response.data;

    document.getElementById('icon_odometer').value = data.odometer;
    document.getElementById('icon_service').value = data.next_service;
    document.getElementById('icon_oil_service').value = data.oil_service;
    document.getElementById('oil_alert').checked = data.oil_alert;
    document.getElementById('service_alert').checked = data.service_alert;
    
    M.updateTextFields();
}).catch((error) => {
    console.log(error);
});

const form = document.getElementById('dbsetupp');
form.addEventListener('submit', handleSubmit);

function handleSubmit(event) {
    event.preventDefault();
    let odometer = document.getElementById('icon_odometer').value;
    let next_service = document.getElementById('icon_service').value;
    let oil_service = document.getElementById('icon_oil_service').value;
    let oil_alert = document.getElementById('oil_alert').checked;
    let service_alert = document.getElementById('service_alert').checked;

    let data = {
        odometer: odometer,
        next_service: next_service,
        oil_service: oil_service,
        oil_alert: oil_alert,
        service_alert: service_alert
    };

    //convert data to form-urlencoded
    let form_data = new URLSearchParams();
    for (let key in data) {
        form_data.append(key, data[key]);
    }

    axios.post('/dbsetupp', form_data).then((response) => {
        M.toast({html: 'Data saved successfully!'});
        // render html response on the entire page
        document.open();
        document.write(response.data);
        document.close();
    }).catch((error) => {
        console.log(error);
        M.toast({html: 'Error saving data!'});
    });
}