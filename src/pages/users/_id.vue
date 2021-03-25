<template>
  <section>
    <h1>User {{$route.params.id}}</h1>
  </section>
</template>


<script>
export default {
  validate({params}) {
    return /^\d+$/.test(params.id);
  }
}
</script>
